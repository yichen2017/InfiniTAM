// Copyright 2014-2015 Isis Innovation Limited and the authors of InfiniTAM

#pragma once

#include "../ITMLib.h"
#include "../Utils/ITMLibSettings.h"

/** \mainpage
    This is the API reference documentation for InfiniTAM. For a general
    overview additional documentation can be found in the included Technical
    Report.

    For use of ITMLib in your own project, the class
    @ref ITMLib::Engine::ITMMainEngine should be the main interface and entry
    point to the library.
*/

namespace ITMLib
{
	/** \brief
	    Main engine, that instantiates all the other engines and
	    provides a simplified interface to them.

	    This class is the main entry point to the ITMLib library
	    and basically performs the whole KinectFusion algorithm.
	    It stores the latest image internally, as well as the 3D
	    world model and additionally it keeps track of the camera
	    pose.

	    The intended use is as follows:
	    -# Create an ITMMainEngine specifying the internal settings,
	       camera parameters and image sizes
	    -# Get the pointer to the internally stored images with
	       @ref GetView() and write new image information to that
	       memory
	    -# Call the method @ref ProcessFrame() to track the camera
	       and integrate the new information into the world model
	    -# Optionally access the rendered reconstruction or another
	       image for visualisation using @ref GetImage()
	    -# Iterate the above three steps for each image in the
	       sequence

	    To access the internal information, look at the member
	    variables @ref trackingState and @ref scene.
	*/
	class ITMMainEngine
	{
	public:
		enum GetImageType
		{
			InfiniTAM_IMAGE_ORIGINAL_RGB,
			InfiniTAM_IMAGE_ORIGINAL_DEPTH,
			InfiniTAM_IMAGE_SCENERAYCAST,
			InfiniTAM_IMAGE_FREECAMERA_SHADED,
			InfiniTAM_IMAGE_FREECAMERA_COLOUR_FROM_VOLUME,
			InfiniTAM_IMAGE_FREECAMERA_COLOUR_FROM_NORMAL,
			InfiniTAM_IMAGE_UNKNOWN
		};

		/// Gives access to the current input frame
		virtual ITMView* GetView(void) = 0;

		/// Gives access to the current camera pose and additional tracking information
		virtual ITMTrackingState* GetTrackingState(void) = 0;

		/// Process a frame with rgb and depth images and optionally a corresponding imu measurement
		virtual void ProcessFrame(ITMUChar4Image *rgbImage, ITMShortImage *rawDepthImage, ITMIMUMeasurement *imuMeasurement = NULL) = 0;

		/// Get a result image as output
		virtual Vector2i GetImageSize(void) const = 0;

		virtual void GetImage(ITMUChar4Image *out, GetImageType getImageType, ITMPose *pose = NULL, ITMIntrinsics *intrinsics = NULL) = 0;

		virtual ~ITMMainEngine() {}
	};
}

