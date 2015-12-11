#ifndef IMAGE_HINT_TRANSFORMER_H
#define IMAGE_HINT_TRANSFORMER_H

#include "lms/module.h"
#include "lms/math/vertex.h"

#include "comm/senseboard.h"
#include "sensor_utils/car.h"
#include "street_environment/trajectory.h"

#include <dlib/control.h>

#include <ctime>
#include <unistd.h>

class TrajectoryPointController : public lms::Module {
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
private:

    street_environment::TrajectoryPoint getTrajectoryPoint();

    void positionController(street_environment::TrajectoryPoint &trajectoryPoint);
    void positionControllerVel();
    void mpcController(double v, double delta_y, double delta_phi, double *steering_front, double *steering_rear);
    double delta_c_h(double phi_s, double te, double v, double y_s);
    double delta_c_v(double phi_s, double te, double v, double y_s, double dh);
    double delta_h(double y_s, double phi_s, double te);
    double delta_v(double y_s, double phi_s, double te, double dh);

    double l = 0.21; //Radstand
    static constexpr size_t MPC_HORIZON = 20;

    struct MpcParameters
    {
        double weight_y, weight_phi, weight_steeringFront, weight_steeringRear, stepSize;
    } mpcParameters;

    dlib::matrix<double,2,1> lower, upper;

    lms::ReadDataChannel<street_environment::Trajectory> trajectory;
    lms::WriteDataChannel<sensor_utils::Car> car;
    /**
     * @brief trajectoryPoint only for debugging
     */
    lms::WriteDataChannel<street_environment::TrajectoryPoint> debugging_trajectoryPoint;


};

#endif /* IMAGE_HINT_TRANSFORMER_H */
