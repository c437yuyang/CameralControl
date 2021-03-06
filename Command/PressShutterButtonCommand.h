

#pragma once

#include "Command.h"
#include "CameraEvent.h"
#include "EDSDK.h"

class PressShutterButtonCommand : public Command
{
private:
	EdsUInt32 _status;

public:
	PressShutterButtonCommand(CameraModel *model, EdsUInt32 status) : _status(status), Command(model){}


	// Execute command	
	virtual bool execute()
	{
		EdsError err = EDS_ERR_OK;
		bool	 locked = false;
		
		//PressShutterButton
		if(err == EDS_ERR_OK)
		{
			err = EdsSendCommand(_model->getCameraObject(), kEdsCameraCommand_PressShutterButton, _status);
		}

		//Notification of error
		if(err != EDS_ERR_OK)
		{
			// It retries it at device busy
			if(err == EDS_ERR_DEVICE_BUSY)
			{
				CameraEvent e("DeviceBusy");
				_model->notifyObservers(&e);
				return true;
			}
			
			CameraEvent e("error", &err); 
			_model->notifyObservers(&e);
		}

		return true;
	}


};