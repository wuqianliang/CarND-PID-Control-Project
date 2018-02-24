#ifndef PID_H
#define PID_H
#include <vector>
class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;


  /*
  * Twiddle variables
  */
  std::vector<double> dp;
  int step, i_th_dp;

  // number of steps to allow changes to settle, then to evaluate error
  int n_settle_steps, n_eval_steps;
  double update_error, best_error;
  bool tried_adding, tried_subtracting, is_twiddle;


  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
   * Helper function
   */
  void Update_Parameter_At_i_th(int, double);

};

#endif /* PID_H */
