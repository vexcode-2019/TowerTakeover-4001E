#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;

auto myChassis = ChassisControllerFactory::create(
  {19, 20}, // Left motors
  {15, 16},   // Right motors
  AbstractMotor::gearset::green, // Torque gearset
  {3.25_in, 8_in} //wheels, wheelbase width

);

auto profileController = AsyncControllerFactory::motionProfile(
  2.5,  // Maximum linear velocity of the Chassis in m/s
   2.0,  // Maximum li..0;p6-9,.near acceleration of the Chassis in m/s/s
  10.0, // Maximum linear jerk of the Chassis in m/s/s/s
  myChassis // Chassis Controller
);


/*
0 -> front blue (3 cube)
1 -> front red (3 cube)
2 -> back blue (5 cube)
3 -> back red (5 cube)
4 -> back blue (6 cube)
5 -> back red (6 cube)
6 -> prog skills blue (20 point, USE RED INSTEAD)
7 -> prog skills red (20 point, use this one)
*/

double square = 0;
double newSquare = 0;
double newDistance = 0;
double mult;

void moveMove(double distance, double speed) { // distance correction code that doesn't go past 6.5 inches

  newDistance = (distance + 0.361) / 3.74;

  myChassis.resetSensors();
  myChassis.setMaxVelocity(speed);
  myChassis.moveDistance(newDistance);

}

void autonhandler(int autonomousPreSet) { // auton main


  if (autonomousPreSet == 0 || autonomousPreSet == 1) { // front blue & red

    intakeHandler(-200);

    tray.move_absolute(750, 100);
    lift.move_absolute(200, 200);

    pros::delay(700);
    pros::delay(500);
    liftHandler(-200);
    trayHandler(-150);
    pros::delay(50);
    intakeHandler(95);
    pros::delay(700);

    autoDrive(-200);
    pros::delay(500);
    intakeHandler(100);
    trayHandler(0);
    liftHandler(0);
    pros::delay(300);
    autoDrive(0);
    pros::delay(200);

    myChassis.setMaxVelocity(300);

    myChassis.moveDistance(1.53_in);
    myChassis.waitUntilSettled();

    pros::delay(500);
    intakeHandler(0);

    myChassis.setMaxVelocity(240);

    if (autonomousPreSet == 1) { // front red
      myChassis.turnAngle(18.5_deg);
    } else { // front blue
      myChassis.turnAngle(-18.5_deg);
    }
    myChassis.waitUntilSettled();

    pros::delay(500);
    intakeHandler(82);

    myChassis.setMaxVelocity(300);

    myChassis.moveDistance(1.53_in);
    myChassis.waitUntilSettled();

    pros::delay(750);
    autoDrive(0);
    intakeHandler(0);

    pros::delay(500);

    myChassis.setMaxVelocity(120);

    if (autonomousPreSet == 1) { // front red
      myChassis.turnAngle(18.5_deg);
    } else { // front blue
      myChassis.turnAngle(-18.5_deg);
    }
    myChassis.waitUntilSettled();


    autoDrive(0);

    pros::delay(500);

    autoDrive(250);
    intakeHandler(-25);
    pros::delay(1050);

    autoDrive(0); //stop drive
    intakeHandler(0);

    pros::delay(500);
    autoDrive(0);
    intakeHandler(-60);
    pros::delay(500);



    trayHandler(210); // deploy tray to stack cubes
    pros::delay(400);
    intakeHandler(-20);
    pros::delay(350);
    intakeHandler(-250);
    pros::delay(500);
    autoDrive(-100);
    pros::delay(500);
    intakeHandler(-200);
    trayHandler(-200);
    pros::delay(700);

    autoDrive(-200);

    tray.move_absolute(0, -100);
    lift.move_absolute(0, -80);
    pros::delay(2000);

    autoDrive(0); // stop all & win auton

  }



  if (autonomousPreSet == 2 || autonomousPreSet == 3) { // back blue & red (5 cube)
    intakeHandler(-200);

tray.move_absolute(750, 100);
lift.move_absolute(200, 200);

pros::delay(700);
pros::delay(500);
liftHandler(-200);
trayHandler(-150);
pros::delay(50);
intakeHandler(95);
pros::delay(700);

autoDrive(-200);
pros::delay(500);
intakeHandler(150);
trayHandler(0);
liftHandler(0);


myChassis.moveDistance(1.68_in);
myChassis.waitUntilSettled();

pros::delay(200); // jerk intake to align cubes
intakeHandler(300);
pros::delay(75);
intakeHandler(-300);
pros::delay(50);
intakeHandler(0);

intakeHandler(0);
myChassis.moveDistance(-1.53_in); //-1.55
myChassis.waitUntilSettled();
myChassis.stop();
driveLF.move_velocity(0);
driveLB.move_velocity(0);
driveRB.move_velocity(0);
driveRF.move_velocity(0);
intakeHandler(0);
pros::delay(400);

if (autonomousPreSet == 2) { // back blue
myChassis.turnAngle(20.86_deg); //   21.2_deg
} else { // back red
myChassis.turnAngle(-20.59_deg); //   21.2_deg
}
myChassis.waitUntilSettled();
myChassis.stop();

autoDrive(150); // drive forward to stacking area
intakeHandler(-25);
pros::delay(1450);

autoDrive(250); // jerk forward to better stack cubes
pros::delay(100);
autoDrive(0); //stop drive

liftHandler(-200);
trayHandler(210); // deploy tray to stack cubes
pros::delay(400);
intakeHandler(-65);
pros::delay(1000);
autoDrive(-60);
intakeHandler(-70);
pros::delay(700);

autoDrive(-200);
pros::delay(250);
liftHandler(50);
intakeHandler(200);
trayHandler(-200);

pros::delay(1500);
autoDrive(0); // stop all & win auton
liftHandler(0);
trayHandler(0);
intakeHandler(0);

  }


if (autonomousPreSet == 4 || autonomousPreSet == 5) { // back blue & red (6 cube)
  intakeHandler(-200);

  tray.move_absolute(750, 100);
  lift.move_absolute(200, 200);

  pros::delay(700);
  pros::delay(500);
  liftHandler(-200);
  trayHandler(-150);
  pros::delay(50);
  intakeHandler(95);
  pros::delay(700);

  autoDrive(-200);
  pros::delay(500);
  intakeHandler(150);
  trayHandler(0);
  liftHandler(0);


  myChassis.moveDistance(1.67_in);
  myChassis.waitUntilSettled();

  intakeHandler(0);

  myChassis.resetSensors();
  pros::delay(300);


  if (autonomousPreSet == 4) { // back blue
  myChassis.turnAngle(-3.9_deg);
} else { // back red
  myChassis.turnAngle(3.9_deg);
  }
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(300);

  myChassis.moveDistance(1.48_in);
  myChassis.waitUntilSettled();

  intakeHandler(200);
  pros::delay(750);
  intakeHandler(0);

  pros::delay(200);
  myChassis.resetSensors();



  intakeHandler(0);

  pros::delay(350);

  if (autonomousPreSet == 4) { // back blue
  myChassis.turnAngle(-21.22_deg);
} else { // back red
  myChassis.turnAngle(21.22_deg);
  }
  myChassis.waitUntilSettled();
  myChassis.stop();

  myChassis.resetSensors();

  autoDrive(400); // drive forward to stacking area
  intakeHandler(-15);
  pros::delay(1450);

  autoDrive(250); // jerk forward to better stack cubes
  pros::delay(100);
  autoDrive(0); //stop drive

  trayHandler(210); // deploy tray to stack cubes
  pros::delay(400);
  intakeHandler(-65);
  pros::delay(1000);
  autoDrive(-60);
  intakeHandler(-70);
  trayHandler(-200);
  pros::delay(700);


    myChassis.resetSensors();
    myChassis.moveDistance(-1_in); // drive backwards from stacking area
    myChassis.waitUntilSettled();
    myChassis.stop();
    liftHandler(0);
     trayHandler(-150);

    pros::delay(1000);

      myChassis.resetSensors();
    myChassis.setMaxVelocity(120);
    myChassis.turnAngle(-16_deg);
    myChassis.waitUntilSettled();
    myChassis.stop();

    pros::delay(1000);

      myChassis.resetSensors();
    lift.move_absolute(300, -80);
    tray.move_absolute(-5, -80);
    autoDrive(350);
    pros::delay(2000);


    // working above ^^

    autoDrive(0);
    pros::delay(500);
      myChassis.resetSensors();

    myChassis.setMaxVelocity(325);
    lift.move_absolute(-10, -100);
    myChassis.moveDistance(-1.2_in); // drive backwards from stacking area
    myChassis.waitUntilSettled();
    myChassis.stop();


    myChassis.resetSensors();

    myChassis.setMaxVelocity(120); // turn towards red side to get cube
    intakeHandler(0);
    myChassis.turnAngle(22.3_deg); /////////////////////////turn//////////////
    myChassis.waitUntilSettled();
    myChassis.stop();

    pros::delay(1000);

      myChassis.resetSensors();

    myChassis.setMaxVelocity(325);
    myChassis.moveDistance(1.8_in); // drive forward and intake cube
    intakeHandler(100);
    myChassis.waitUntilSettled();
    myChassis.stop();

    pros::delay(1000);

    intakeHandler(0);
      myChassis.resetSensors();
    lift.move_absolute(300, -80);

    pros::delay(1000);

    intakeHandler(-100); // get cube in tower by de-intaking
    pros::delay(1000);
    autoDrive(0);

}



if (autonomousPreSet == 6 || autonomousPreSet == 7) { //skilzz

  intakeHandler(-200); // flipout
  tray.move_absolute(750, 100);
  lift.move_absolute(150, 200);
  pros::delay(700);
  pros::delay(500);
  liftHandler(-200);
  trayHandler(-150);
  pros::delay(50);
  intakeHandler(95);
  pros::delay(700);

  autoDrive(-200); // drive back to wall align
  pros::delay(1000);
  intakeHandler(150);
  trayHandler(0);
  liftHandler(0);


  myChassis.moveDistance(1.67_in); // drive forward to intake cubes
    myChassis.waitUntilSettled();

    pros::delay(200); // jerk intake to align cubes
    intakeHandler(300);
    pros::delay(50);
    intakeHandler(-300);
    pros::delay(75);
    intakeHandler(0);

    intakeHandler(0);
    myChassis.moveDistance(-1.53_in); // drive backwards with cubes
    myChassis.waitUntilSettled();
    myChassis.stop();
    driveLF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
    driveRF.move_velocity(0);
    intakeHandler(0);
    pros::delay(50);

    myChassis.turnAngle(20.92_deg); //  turn towards scoring zone //20.88
    myChassis.waitUntilSettled();
    myChassis.stop();

    autoDrive(150); // drive forward to stacking area
    intakeHandler(-13);
    pros::delay(2000);

    autoDrive(0); //stop drive

    intakeHandler(0); // stack
    liftHandler(-200);
    trayHandler(100);
    pros::delay(3300);
    trayHandler(0);
    pros::delay(750);
    autoDrive(200);
    pros::delay(175);
    autoDrive(0);
    pros::delay(500);
    autoDrive(-60);
    pros::delay(700);
    intakeHandler(0);
    pros::delay(500);

    trayHandler(-200);
    liftHandler(0);

    pros::delay(500);

  myChassis.resetSensors();
  myChassis.moveDistance(-1.493_in); // drive backwards from stacking area
  myChassis.waitUntilSettled();
  myChassis.stop();
  trayHandler(-200);
  pros::delay(500);
  trayHandler(0);
  pros::delay(500);

  intakeHandler(0);
  pros::delay(400);



////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// going for 10 after this ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

  myChassis.resetSensors();
  myChassis.setMaxVelocity(150); // turn towards red side to get cube
  intakeHandler(0);
  myChassis.turnAngle(-21.04_deg); /////////////////////////turn//////////////
  myChassis.waitUntilSettled();
  myChassis.stop();


  intakeHandler(150);
  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(1.56_in); // drive forward and intake cube
  myChassis.waitUntilSettled();
  myChassis.stop();
  pros::delay(50);
  intakeHandler(-10);

  pros::delay(750);

  myChassis.resetSensors();
  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(-0.9_in);// drive back to clear tower
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(500);

  lift.move_absolute(215, -80); // lift up arms
  pros::delay(200);
  lift.set_brake_mode(MOTOR_BRAKE_BRAKE);

  pros::delay(1000);

  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(1_in); // drive forward to score tower
  myChassis.waitUntilSettled();
  myChassis.stop();
  intakeHandler(0);

  pros::delay(1000);
  intakeHandler(-40); // get cube in tower by de-intaking
  autoDrive(-10);
  pros::delay(1300);

  myChassis.resetSensors();
  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(-1.58_in);// drive back to clear tower
  myChassis.waitUntilSettled();
  myChassis.stop();
  pros::delay(1000);

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// going for 15 after this ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

  pros::delay(50);
  liftHandler(-200);
  pros::delay(1000); // put arms down
  liftHandler(0);
  pros::delay(500);

  myChassis.resetSensors();
  myChassis.setMaxVelocity(200);
  intakeHandler(0);
  myChassis.turnAngle(-20.374_deg); // turn towards protected zone mid tower /////////////////////////turn//////////////

  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(500);

  intakeHandler(200);
  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(1.6_in); // drive forward and intake cube
  myChassis.waitUntilSettled();
  myChassis.stop();
  pros::delay(50);
  intakeHandler(-15);

  pros::delay(750);

  myChassis.resetSensors();
  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(-0.85_in);// drive back to clear tower
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(500);

  myChassis.resetSensors();
  lift.set_brake_mode(MOTOR_BRAKE_BRAKE);
  lift.move_absolute(320, -80); // arms up

  pros::delay(500);

  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(1.2_in); // drive forward to score tower
  intakeHandler(100);
  myChassis.waitUntilSettled();
  myChassis.stop();
  intakeHandler(0);

  pros::delay(500);

  intakeHandler(-50); // get cube in tower by de-intaking

  pros::delay(1250);

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// going for 20 after this ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

  myChassis.resetSensors();
  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(-0.85_in);// drive back from tower
  myChassis.waitUntilSettled();
  myChassis.stop();

  intakeHandler(0);  // bring down arms
  pros::delay(500);
  liftHandler(-200);
  pros::delay(1000);
  liftHandler(0);
  pros::delay(500);

  myChassis.resetSensors();
  myChassis.setMaxVelocity(200); // turn towards line of cubes
  myChassis.turnAngle(20.32_deg); /////////////////////////turn//////////////
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1000);

  intakeHandler(150);



    myChassis.resetSensors();
    myChassis.setMaxVelocity(325);
    myChassis.moveDistance(-1_in);// drive towards line of cubes and intake
    myChassis.waitUntilSettled();
    myChassis.stop();

    pros::delay(500);

    myChassis.resetSensors();
    myChassis.setMaxVelocity(325);
    myChassis.moveDistance(1_in);// drive towards line of cubes and intake
    myChassis.waitUntilSettled();
    myChassis.stop();

    pros::delay(1000);

  myChassis.resetSensors();
  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(1.5_in);// drive towards line of cubes and intake
  myChassis.waitUntilSettled();
  myChassis.stop();

  intakeHandler(0);

  pros::delay(1000);

  myChassis.resetSensors();
  myChassis.setMaxVelocity(200); // turn towards alliance tower
  myChassis.turnAngle(20.685_deg); /////////////////////////turn//////////////
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1000);

  myChassis.resetSensors();
  lift.move_absolute(220, -80); // lift up arms
  pros::delay(200);
  lift.set_brake_mode(MOTOR_BRAKE_BRAKE);

  pros::delay(1000);

  myChassis.resetSensors();
  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(1.8_in);// drive towards alliance tower
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1000);

  intakeHandler(-40); // de-intake to score
  autoDrive(-17);

  pros::delay(1000);

  autoDrive(-200); // drive back from tower and win prog skills
  pros::delay(1000);
  autoDrive(0);

}
}
