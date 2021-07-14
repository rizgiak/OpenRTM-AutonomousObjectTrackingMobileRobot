// -*- C++ -*-
/*!
 * @file  RobotController.cpp
 * @brief Robot Controller component
 * @date $Date$
 *
 * $Id$
 */

#include "RobotController.h"

// Module specification
// <rtc-template block="module_spec">
static const char* robotcontroller_spec[] =
  {
    "implementation_id", "RobotController",
    "type_name",         "RobotController",
    "description",       "Robot Controller component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Controller",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.speed_x", "0.0",
    "conf.default.speed_r", "0.0",
    "conf.default.stop_d", "30",

    // Widget
    "conf.__widget__.speed_x", "slider.0.01",
    "conf.__widget__.speed_r", "slider.0.01",
    "conf.__widget__.stop_d", "text",
    // Constraints
    "conf.__constraints__.speed_x", "-1.5<x<1.5",
    "conf.__constraints__.speed_r", "-2.0<x<2.0",

    "conf.__type__.speed_x", "double",
    "conf.__type__.speed_r", "double",
    "conf.__type__.stop_d", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RobotController::RobotController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in),
    m_x_inIn("x_in", m_x_in),
    m_y_inIn("y_in", m_y_in),
    m_outOut("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RobotController::~RobotController()
{
}



RTC::ReturnCode_t RobotController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  addInPort("x_in", m_x_inIn);
  addInPort("y_in", m_y_inIn);

  // Set OutPort buffer
  addOutPort("out", m_outOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("speed_x", m_speed_x, "0.0");
  bindParameter("speed_r", m_speed_r, "0.0");
  bindParameter("stop_d", m_stop_d, "30");
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotController::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RobotController::onActivated(RTC::UniqueId ec_id)
{
  // Sensor value initialization
  for (int i = 0; i < 4; i++)
  {
    sensor_data[i] = 0;
  }
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotController::onDeactivated(RTC::UniqueId ec_id)
{
  // Stop the robot
  m_out.data.vx = 0;
  m_out.data.va = 0;
  m_outOut.write();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotController::onExecute(RTC::UniqueId ec_id)
{
  // Confirm the existence of input data
  if (m_inIn.isNew())
  {
    // Read input data
    m_inIn.read();
    for (int i = 0; i < m_in.data.length(); i++)
    {
      // Input data storage
      if (i < 4)
      {
        sensor_data[i] = m_in.data[i];
      }
    }
  }

  if (m_x_inIn.isNew())
  {
    m_x_inIn.read();
    m_speed_r = (float)(m_x_in.data / 320.0);
  }

  if (m_y_inIn.isNew())
  {
    m_y_inIn.read();
    m_speed_x = (float)(m_y_in.data / 320.0);
  }

  


  printf("X:%1.2f, R:%1.2f\n",m_speed_x, m_speed_r);

  // Determine if you want to stop only when moving forward
  if (m_speed_x > 0)
  {
    for (int i = 0; i < 4; i++)
    {
      // Determine if the sensor value is greater than or equal to the set value
      if (sensor_data[i] > m_stop_d)
      {
        // Stop if the sensor value is greater than or equal to the set value
        m_out.data.vx = 0;
        m_out.data.va = 0;
        m_outOut.write();
        return RTC::RTC_OK;
      }
    }
  }
  // If there is no sensor with a value higher than the set value, operate with the value of the configuration parameter
  m_out.data.vx = m_speed_x;
  m_out.data.va = m_speed_r;
  m_outOut.write();
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void RobotControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(robotcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<RobotController>,
                             RTC::Delete<RobotController>);
  }

};


