/**
 * @file argos3/core/utility/logging/argos_log.h
 *
 * @brief This file provides the ARGoSLogger class.
 *
 * The LOG and LOGERR statements write to standard out and standard err,
 * respectively. LOG is meant to report normal events that are considered
 * interesting for the user. LOGERR reports errors and warning the user
 * must consider during an experimental run. Their usage is identical to
 * the standard C++ statements std::cout and std::cerr. In fact, LOG and
 * LOGERR redirect these streams.
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef ARGOSLOG_H
#define ARGOSLOG_H

#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#ifdef ARGOS_THREADSAFE_LOG
#include <pthread.h>
#include <sstream>
#include <map>
#include <vector>
#endif

namespace argos {
   class CARGOSLogger;
}

#include <argos3/core/utility/logging/argos_colored_text.h>

namespace argos {

   class CARGoSLog {

   private:

      /** The stream to write to */
      std::ostream& m_cStream;

      /** The default output color */
      SLogColor m_sLogColor;

      /** True when we want to use color */
      bool m_bColoredOutput;

#ifdef ARGOS_THREADSAFE_LOG
      /** Maps a thread to its visualization order */
      std::map<pthread_t, size_t> m_mapStreamOrder;

      /** Contains the buffer streams */
      std::vector<std::stringstream*> m_vecStreams;

      /** The mutex to protect the operations on the buffers */
      pthread_mutex_t m_tMutex;
#endif

   public:

      CARGoSLog(std::ostream& c_stream,
                const SLogColor& s_log_color,
                bool b_colored_output_enabled = true) :
         m_cStream(c_stream),
         m_sLogColor(s_log_color),
         m_bColoredOutput(b_colored_output_enabled) {
#ifdef ARGOS_THREADSAFE_LOG
         pthread_mutex_init(&m_tMutex, NULL);
         AddThreadSafeBuffer();
#endif
      }

      ~CARGoSLog() {
#ifdef ARGOS_THREADSAFE_LOG
         pthread_mutex_destroy(&m_tMutex);
         while(!m_vecStreams.empty()) {
            delete m_vecStreams.back();
            m_vecStreams.pop_back();
         }
#endif
      }

      inline void EnableColoredOutput() {
         m_bColoredOutput = true;
      }

      inline void DisableColoredOutput() {
         m_bColoredOutput = false;
      }

      inline bool IsColoredOutput() const {
         return m_bColoredOutput;
      }

      inline std::ostream& GetStream() {
         return m_cStream;
      }

#ifdef ARGOS_THREADSAFE_LOG
      inline void Flush() {
         pthread_mutex_lock(&m_tMutex);
         for(size_t i = 0; i < m_vecStreams.size(); ++i) {
            m_cStream << m_vecStreams[i]->str();
            m_vecStreams[i]->str("");
         }
         pthread_mutex_unlock(&m_tMutex);
      }

      inline void AddThreadSafeBuffer() {
         pthread_mutex_lock(&m_tMutex);
         m_mapStreamOrder.insert(std::make_pair<pthread_t, size_t>(pthread_self(), m_vecStreams.size()));
         m_vecStreams.push_back(new std::stringstream);
         pthread_mutex_unlock(&m_tMutex);
      }
#endif
      
      inline CARGoSLog& operator<<(std::ostream& (*c_stream)(std::ostream&)) {
#ifdef ARGOS_THREADSAFE_LOG
         *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << c_stream;
#else
         m_cStream << c_stream;
#endif
         return *this;
      }

      inline CARGoSLog& operator<<(const std::_Setw& t_msg) {
#ifdef ARGOS_THREADSAFE_LOG
         *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << t_msg;
#else
         m_cStream << t_msg;
#endif
         return *this;
      }

      inline CARGoSLog& operator<<(const std::_Setiosflags& t_msg) {
#ifdef ARGOS_THREADSAFE_LOG
         *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << t_msg;
#else
         m_cStream << t_msg;
#endif
         return *this;
      }

      template <typename T> CARGoSLog& operator<<(const T t_msg) {
         if(m_bColoredOutput) {
#ifdef ARGOS_THREADSAFE_LOG
            *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << m_sLogColor << t_msg << reset;
#else
            m_cStream << m_sLogColor << t_msg << reset;
#endif
         }
         else {
#ifdef ARGOS_THREADSAFE_LOG
            *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << t_msg;
#else
            m_cStream << m_sLogColor << t_msg << reset;
#endif
         }
         return *this;
      }

   };

   extern CARGoSLog LOG;
   extern CARGoSLog LOGERR;

}

#define RLOG    LOG    << "[" << GetRobot().GetRobotId() << "] "
#define RLOGERR LOGERR << "[" << GetRobot().GetRobotId() << "] "

#endif
