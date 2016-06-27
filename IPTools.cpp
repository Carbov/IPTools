// This is the main DLL file.

#include "stdafx.h"

#include "IPTools.h"


namespace IPTools {

	
	Bitmap^ IPTools1::Formater(Bitmap^ bmp, PixelFormat pf)
	{

		Bitmap^ ret = (Bitmap^)bmp->Clone(Rectangle(0, 0, bmp->Width, bmp->Height), pf);

		if (pf == PixelFormat::Format8bppIndexed)
		{
			ColorPalette^ cp = ret->Palette;
			cp->Entries[0] = Color::FromArgb(0, 0, 0);
			for (int i = 1; i < cp->Entries->Length; i++)
			{
				cp->Entries[i] = Color::FromArgb(255, 255, 255);
			}
			ret->Palette = cp;
		}
		return ret;
	}
	
	
	Bitmap^ IPTools1::Noc(Bitmap^ src, int bord, Color clr, bool plus)
	{
		src = Formater(src, PixelFormat::Format24bppRgb);
		
		Bitmap^ ret = (Bitmap^)src->Clone();;
		Rectangle rect = Rectangle(0, 0, ret->Width, ret->Height);
		BitmapData^ retData = ret->LockBits(
			rect, ImageLockMode::ReadWrite, PixelFormat::Format24bppRgb);
		rect = Rectangle(0, 0, ret->Width, ret->Height);
		BitmapData^ srcData = src->LockBits(
			rect,
			ImageLockMode::ReadWrite, PixelFormat::Format24bppRgb);



		int stride = srcData->Stride;

		retData->Scan0.ToPointer();
		
		uchar* ret_ = (uchar*)retData->Scan0.ToPointer();
		uchar* src_ = (uchar*)srcData->Scan0.ToPointer();

			for (int i = 0; i < src->Height; i++)
			{

				int dop = stride * i;


				for (int j = 0; j < src->Width; j++)
				{
					int dopp = dop + j * 3;
					//int dopp3 = dop3 + j;
					int av = (src_[dopp] + src_[dopp + 1] + src_[dopp + 2]) / 3;
					bool cond;
					if (plus)
						cond = (av > bord);
					else
						cond = (av < bord);
					if (cond)
					{
						ret_[dopp] = clr.B;
						ret_[dopp + 1] = clr.G;
						ret_[dopp + 2] = clr.R;
						/*ret_[dopp] = 0;
						ret_[dopp + 1] = 0;
						ret_[dopp + 2] = 0;*/
					}
					else
					{
						ret_[dopp] = src_[dopp];
						ret_[dopp + 1] = src_[dopp + 1];
						ret_[dopp + 2] = src_[dopp + 2];
					}


				}
		}

		src->UnlockBits(srcData);
		ret->UnlockBits(retData);
		return ret;
	}
}