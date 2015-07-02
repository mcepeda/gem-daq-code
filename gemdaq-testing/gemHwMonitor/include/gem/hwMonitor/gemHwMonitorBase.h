#ifndef gem_hwMonitor_gemHwMonitorBase_h
#define gem_hwMonitor_gemHwMonitorBase_h

#include <string>
#include <vector>
#include <cstdlib>

#include "xdaq/Application.h"
#include "xgi/framework/Method.h"

#include "gem/utils/GEMLogging.h"
#include "gem/utils/gemXMLparser.h"
#include "gem/utils/gemComplexDeviceProperties.h"
#include "gem/utils/gemDeviceProperties.h"

namespace gem {
  namespace hwMonitor {
    template <class T>
      class gemHwMonitorBase
      {
      public:
	gemHwMonitorBase()
	  throw (xdaq::exception::Exception) :
	gemLogger_(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("gemHwMonitorLogger")))
	  {
	    gemDevice_ = new T();
	    //gemLogger_.setLogLevel(DEBUG_LOG_LEVEL);
	  }
	
	virtual ~gemHwMonitorBase()
	  {
	    delete gemDevice_;
	  }

	bool isConfigured()
	  throw (xgi::exception::Exception)
	{return isConfigured_;}

	void setIsConfigured(bool state)
	//throw (xgi::exception::Exception)
	{
	  INFO("isConfigured_(" << isConfigured_ << ")");
	  INFO("setIsConfigured(state = " << state << ")");
	  isConfigured_=state;
	  INFO("isConfigured_(" << isConfigured_ << ") = state");
	}

	const std::string getDeviceId()
	  throw (xgi::exception::Exception);

	/**
	 *   Get subdevice status
	 *   0 - device is working well, 1 - device has errors, 2 - device status unknown
	 */
	unsigned int getSubDeviceStatus (unsigned int i)
	//throw (xgi::exception::Exception)
	{return subDeviceStatus_.at(i);}

	/**
	 *   Set subdevice status
	 *   0 - device is working well, 1 - device has errors, 2 - device status unknown
	 */
	void setSubDeviceStatus (const unsigned int deviceStatus, const unsigned int i)
	  throw (xgi::exception::Exception)
	{subDeviceStatus_.at(i) = deviceStatus;}

	/**
	 *   Add subdevice status
	 *   0 - device is working well, 1 - device has errors, 2 - device status unknown
	 */
	void addSubDeviceStatus (unsigned int deviceStatus)
	  throw (xgi::exception::Exception)
	{subDeviceStatus_.push_back(deviceStatus);}

	/**
	 *   Get device status
	 *   0 - device is working well, 1 - device has errors, 2 - device status unknown
	 */
	unsigned int getDeviceStatus ()
	  throw (xgi::exception::Exception)
	{return deviceStatus_;}

	/**
	 *   Set device status
	 *   0 - device is working well, 1 - device has errors, 2 - device status unknown
	 */
	void setDeviceStatus (const unsigned int deviceStatus)
	  throw (xgi::exception::Exception)
	{deviceStatus_ = deviceStatus;}
	/**
	 *   Set device configuration
	 */
	void setDeviceConfiguration(T& device)
	  throw (xgi::exception::Exception);
	/**
	 *   Get device reference
	 */
	T*  getDevice()
	  throw (xgi::exception::Exception)
	  {return gemDevice_;}

	int getNumberOfSubDevices()
	  throw (xgi::exception::Exception);

	const std::string getCurrentSubDeviceId(unsigned int subDeviceNumber)
	  throw (xgi::exception::Exception);

	/**
	 *   Access to board utils
	 virtual void boardUtils ()
	 throw (xgi::exception::Exception);
	*/
      protected:
      private:
	bool isConfigured_;
	unsigned int deviceStatus_; // 0 - device is working well, 1 - device has errors, 2 - device status unknown
	std::vector<unsigned int> subDeviceStatus_; // 0 - device is working well, 1 - device has errors, 2 - device status unknown

	log4cplus::Logger gemLogger_;

	std::string xmlConfigFileName_;
	T* gemDevice_;
      };

    typedef gemHwMonitorBase<gem::utils::gemSystemProperties> gemHwMonitorSystem;
    typedef gemHwMonitorBase<gem::utils::gemCrateProperties> gemHwMonitorCrate;
    typedef gemHwMonitorBase<gem::utils::gemGLIBProperties> gemHwMonitorGLIB;
    typedef gemHwMonitorBase<gem::utils::gemOHProperties> gemHwMonitorOH;
    typedef gemHwMonitorBase<gem::utils::gemVFATProperties> gemHwMonitorVFAT;
  } // end namespace hwMon
} // end namespace gem
#endif
