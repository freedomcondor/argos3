/**
 * @file <argos3/plugins/robots/drone/simulator/drone_flight_system_default_actuator.cpp>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#include "drone_flight_system_default_actuator.h"

#include <argos3/core/utility/logging/argos_log.h>

#include <argos3/plugins/robots/drone/simulator/drone_flight_system_entity.h>
#include <argos3/plugins/robots/drone/simulator/drone_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   CDroneFlightSystemDefaultActuator::CDroneFlightSystemDefaultActuator() :
      m_pcFlightSystemEntity(nullptr) {}

   /****************************************/
   /****************************************/

   CDroneFlightSystemDefaultActuator::~CDroneFlightSystemDefaultActuator() {}
   
   /****************************************/
   /****************************************/

   void CDroneFlightSystemDefaultActuator::SetRobot(CComposableEntity& c_entity) {
      m_pcFlightSystemEntity = 
         &(c_entity.GetComponent<CDroneFlightSystemEntity>("flight_system"));
   }

   /****************************************/
   /****************************************/
   
   void CDroneFlightSystemDefaultActuator::Init(TConfigurationNode& t_tree) {
      try {
         CCI_DroneFlightSystemActuator::Init(t_tree);
         bool bIdealMode = false;
         GetNodeAttributeOrDefault(t_tree, "ideal_mode", bIdealMode, bIdealMode);
         m_pcFlightSystemEntity->SetIdealMode(bIdealMode);
         bool bVelocityMode = false;
         GetNodeAttributeOrDefault(t_tree, "velocity_mode", bVelocityMode, bVelocityMode);
         m_pcFlightSystemEntity->SetVelocityMode(bVelocityMode);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in the drone flight system actuator.", ex);
      }
   }
  
   /****************************************/
   /****************************************/

   void CDroneFlightSystemDefaultActuator::Update() {
      m_pcFlightSystemEntity->SetTargetPosition(m_cTargetPosition);
      m_pcFlightSystemEntity->SetTargetVelocity(m_cTargetVelocity);
      m_pcFlightSystemEntity->SetTargetYawAngle(m_cTargetYawAngle);
      m_pcFlightSystemEntity->SetTargetYawVelocity(m_cTargetYawVelocity);
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CDroneFlightSystemDefaultActuator,
                     "drone_flight_system", "default",
                     "Michael Allwright [allsey87@gmail.com]",
                     "1.0",
                     "The drone flight system actuator.",
                     "This actuator simulates the interface to a PX4 flight controller.",
                     "Usable"
   );

   /****************************************/
   /****************************************/
   
}
