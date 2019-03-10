/*             
    Arjav Patel - Sample FRC Robot Code
    February 18, 2019
    Task:
        - Control robot movement with joystick
        - Ensure that robot is only facing one direction the entire time
        - Robot moves in the same direction the joystick is being pushed in
        - Speed of robot is determined by how severe the joystick is being pushed
        - Robot only moves at 30% power
*/

import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.Servo;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.Joystick;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.ctre.phoenix.motorcontrol.can.WPI_TalonSRX;

public class Robot extends TimedRobot {

    //Instantiate global motors, joystick, timer and variables
    TalonSRX talons = new TalonSRX[] {TalonSRX(10), TalonSRX(11), TalonSRX(12), TalonSRX(13)};
    TalonSRX azimuth = new TalonSRX[] {TalonSRX(0), TalonSRX(1), TalonSRX(2), TalonSRX(3)};
    Joystick j1 = new Joystick(1);
    Timer time1 = new Timer();
    int state = 0;
    final int ENCODER_VAL = 4100;
    double velocity = 0;
    double x = 0;
    double y = 0;
    double angle = 0;

    //Fuction to set the azimuth motors to a certain position
    public void azmControl(int pos) {
        for (int i = 0; i < 4; ++i) {
            azimuth[i].set(com.ctre.phoenix.motorcontrol.ControlMode.Position, pos);
        }
    }

    //Fuction to set the drive motots to a certain speed based on the values mapped by joystick
    public void talonSpeed(double speed) {
        for (int i = 10; i < 14; ++i) {
            talons[i].set(com.ctre.phoenix.motorcontrol.ControlMode.Position, speed);
        }
    }

    //Runs once and always resets state to 0
    @Override
    public void teleopInit() {
        state = 0;
    }

    //Continuously loops every couple of milliseconds
    @Override
    public void teleopPeriodic() {
        
        //Always get updated x and y values of the joystick position
        //Set the azimuth motors facing the same direction
        x = j1.getAxis(Joystick.AxisType.kX);
        y = j1.getAxis(Joystick.AxisType.kY) * -1;
        azmControl(0);

        //Determine motor fuction based on state
        switch (state) {
            
            //If the joystick is not being moved, stop the robot
            case 0:
                talonSpeed(0);
                
                //If user moves joystick, move to next case
                if (y != 0 || x != 0) {
                    state = 1;
                }
            break;  
                
            //If joystick is not center, move robot    
            case 1:
                
                //If user stop moving joystick, stop robot
                if(y == 0 && x == 0) {
                    state = 0;
                }

                //Get the angle of the joystick with atan fuction
                //Turn the azimuth to the specified angle
                if(y < 0) {
                    angle = (2 * Math.PI) + Math.atan2(y,x);
                }
                else {
                    angle = Math.atan2(y, x);
                }
                azmControl ((int) (angle / (2 * Math.PI) * ENCODER_VAL) - (ENCODER_VAL / 4));
                
                //Use the x value, y value and pythagorean theorem to determine of far off center the joystick is (More off center = faster robot moves)
                //Set the speed to 30% power to conserve battery
                velocity = Math.sqrt( Math.pow(y, 2) + Math.pow(x, 2));
                talonSpeed(velocity * 0.3); 
            break;    
        }
    }

    @Override
    public void autonomousInit() {
    }

    @Override
    public void autonomousPeriodic() {
    }
}
