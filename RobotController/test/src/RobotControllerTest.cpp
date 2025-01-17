﻿// -*- C++ -*-
/*!
 * @file  RobotControllerTest.cpp
 * @brief Robot Controller component
 * @date $Date$
 *
 * $Id$
 */

#include "RobotControllerTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* robotcontroller_spec[] =
  {
    "implementation_id", "RobotControllerTest",
    "type_name",         "RobotControllerTest",
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
RobotControllerTest::RobotControllerTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in),
    m_x_inIn("x_in", m_x_in),
    m_y_inIn("y_in", m_y_in),
    m_vel_inIn("vel_in", m_vel_in),
    m_outOut("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RobotControllerTest::~RobotControllerTest()
{
}



RTC::ReturnCode_t RobotControllerTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("out", m_outIn);

  // Set OutPort buffer
  addOutPort("in", m_inOut);
  addOutPort("x_in", m_x_inOut);
  addOutPort("y_in", m_y_inOut);
  addOutPort("vel_in", m_vel_inOut);

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
RTC::ReturnCode_t RobotControllerTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotControllerTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotControllerTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RobotControllerTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotControllerTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotControllerTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotControllerTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotControllerTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotControllerTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotControllerTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotControllerTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void RobotControllerTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(robotcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<RobotControllerTest>,
                             RTC::Delete<RobotControllerTest>);
  }

};


