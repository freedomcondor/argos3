/**
 * @file <argos3/plugins/robots/drone/simulator/drone_flight_system_entity.h>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#ifndef DRONE_FLIGHT_SYSTEM_ENTITY_H
#define DRONE_FLIGHT_SYSTEM_ENTITY_H

namespace argos {
   class CDroneFlightSystemEntity;
}

#include <argos3/core/simulator/entity/entity.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>

namespace argos {

   class CDroneFlightSystemEntity : public CEntity {

   public:

      ENABLE_VTABLE();

   public:

      CDroneFlightSystemEntity(CComposableEntity* pc_parent);

      CDroneFlightSystemEntity(CComposableEntity* pc_parent,
                               const std::string& str_id);

      /**
       * @brief Destructor.
       */
      virtual ~CDroneFlightSystemEntity() {}

      virtual void Update() {}

      virtual void Reset();

      void SetPositionReading(const CVector3& c_reading) {
         m_cPositionReading = c_reading;
      }

      const CVector3& GetPositionReading() const {
         return m_cPositionReading;
      }

      void SetOrientationReading(const CVector3& c_reading) {
         m_cOrientationReading = c_reading;
      }

      const CVector3& GetOrientationReading() const {
         return m_cOrientationReading;
      }

      void SetVelocityReading(const CVector3& c_reading) {
         m_cVelocityReading = c_reading;
      }

      const CVector3& GetVelocityReading() const {
         return m_cVelocityReading;
      }

      void SetAngularVelocityReading(const CVector3& c_reading) {
         m_cAngularVelocityReading = c_reading;
      }

      const CVector3& GetAngularVelocityReading() const {
         return m_cAngularVelocityReading;
      }

      void SetTargetPosition(const CVector3& c_position) {
         m_cTargetPosition = c_position;
      }

      const CVector3& GetTargetPosition() const {
         return m_cTargetPosition;
      }

      void SetTargetVelocity(const CVector3& c_velocity) {
         m_cTargetVelocity = c_velocity;
      }

      const CVector3& GetTargetVelocity() const {
         return m_cTargetVelocity;
      }

      void SetTargetYawAngle(const CRadians f_yaw_angle) {
         m_fTargetYawAngle = f_yaw_angle;
      }

      const CRadians& GetTargetYawAngle() const {
         return m_fTargetYawAngle;
      }

      void SetTargetYawVelocity(const CRadians f_yaw_velocity) {
         m_fTargetYawVelocity = f_yaw_velocity;
      }

      const CRadians& GetTargetYawVelocity() const {
         return m_fTargetYawVelocity;
      }

      virtual std::string GetTypeDescription() const {
         return "flight_system";
      }

      void SetIdealMode(const bool b_ideal_mode) {
         m_bIdealMode = b_ideal_mode;
      }

      const bool GetIdealMode() const {
         return m_bIdealMode;
      }

      void SetVelocityMode(const bool b_velocity_mode) {
         m_bVelocityMode = b_velocity_mode;
      }

      const bool GetVelocityMode() const {
         return m_bVelocityMode;
      }

   private:
      CVector3 m_cPositionReading;
      CVector3 m_cOrientationReading;
      CVector3 m_cVelocityReading;
      CVector3 m_cAngularVelocityReading;
      CVector3 m_cTargetPosition;
      CVector3 m_cTargetVelocity;
      CRadians m_fTargetYawAngle;
      CRadians m_fTargetYawVelocity;
      bool m_bIdealMode;
      bool m_bVelocityMode;
   };
}

#endif
