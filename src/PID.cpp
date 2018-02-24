#include "PID.h"
#include <cmath>
#include <iostream>
#include <limits>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {

	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;

    // Twiddling parameters
    is_twiddle = false;
    dp = {0.1*Kp,0.1*Kd,0.1*Ki};
    step = 1;
    i_th_dp = 2;  // this will wrao back to 0 after the first twiddle loop
    n_settle_steps = 100;
    n_eval_steps = 100;
    update_error = 0;
    best_error = std::numeric_limits<double>::max();
    tried_adding = false; 
    tried_subtracting = false;

}

void PID::UpdateError(double cte) {

        d_error = cte - p_error; 	/*diff_cte*/
        i_error += cte ; 		/*int_cte*/
        p_error = cte ;			/*prev_cte*/


    	// update total error only if we're past number of settle steps
    	if (step % (n_eval_steps + n_settle_steps) > n_settle_steps){
        	update_error += pow(cte,2);
    	}

    // last step in twiddle loop... twiddle it?
    if (is_twiddle && step % (n_eval_steps + n_settle_steps) == 0){
        

        update_error /= n_eval_steps*1.0;

        cout << "step: " << step << endl;
        cout << "total error: " << update_error << endl;
        cout << "best error: " << best_error << endl;
        if (update_error < best_error) {
            cout << "improvement!" << endl;
            best_error = update_error;
            //  Skip first time through
            if (step >  (n_settle_steps + n_eval_steps)) {
                dp[i_th_dp] *= 1.1;            
            }
            // next parameter
            i_th_dp = (i_th_dp + 1) % 3;
            tried_adding = tried_subtracting = false;
        }
        if (!tried_adding && !tried_subtracting) {
            // try adding dp[i] to params[i]
            Update_Parameter_At_i_th(i_th_dp, dp[i_th_dp]);
            tried_adding = true;
        }
        else if (tried_adding && !tried_subtracting) {
            // try subtracting dp[i] from params[i]
            Update_Parameter_At_i_th(i_th_dp, -2 * dp[i_th_dp]);     
            tried_subtracting = true;         
        }
        else {
            // set it back, reduce dp[i], move on to next parameter
            Update_Parameter_At_i_th(i_th_dp, dp[i_th_dp]);      
            dp[i_th_dp] *= 0.9;
            // next parameter
            i_th_dp = (i_th_dp + 1) % 3;
            tried_adding = tried_subtracting = false;
        }
        update_error = 0;
        cout << "new parameters" << endl;
        cout << "P: " << Kp << ", I: " << Ki << ", D: " << Kd << endl;        
    }
    step++;
    cout << "step : " << step << endl;
}

double PID::TotalError() {

	return -Kp * p_error - Kd * d_error - Ki * i_error;
}

void PID::Update_Parameter_At_i_th(int index, double delta) {
    if (index == 0) {
        Kp += delta;
    }
    else if (index == 1) {
        Kd += delta;
    }
    else if (index == 2) {
        Ki += delta;
    }
    else {
        std::cout << "Index out of bounds";
    }
}

