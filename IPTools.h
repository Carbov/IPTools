// IPTools.h

#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;


using namespace cv;

namespace IPTools {


	public ref class IPTools1
	{
	public:

		static Bitmap^ Noc(Bitmap^ src, int bord, Color clr, bool plus);
		static Bitmap^ Formater(Bitmap^ bmp, PixelFormat pf);
		
	};
}
