/*
 * main.cpp
 *
 *  Created on: Jun 25, 2017
 *      Author: xwong
 */

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>

#include "input.h"
#include "featureManager.h"

/// argument parser
void argumentParser(int argc, char** argv, std::string& fileExt, std::string& fileName,
		std::string& camCalibfile,std::string& optionFile, int& initCounter)
{

	for(int i =0; i < argc; i++)
	{
		if(strcmp("-e",argv[i])== 0)
		{
			fileExt = std::string(argv[i+1]);
		}
		else
		if(strcmp("-f",argv[i])== 0)
		{
			fileName = std::string(argv[i+1]);
		}
		else
		if(strcmp("-c",argv[i])== 0)
		{
			camCalibfile = std::string(argv[i+1]);
		}
		else
		if(strcmp("-o",argv[i])== 0)
		{
			optionFile = std::string(argv[i+1]);
		}
		else
		if(strcmp("-i",argv[i])== 0)
		{
			initCounter = atoi(argv[i+1]);
		}
	}
}



int main(int argc, char** argv) {

	featureManager featMng;

	std::string fileExt, fileName, camCalibFile, optionFile;
	int initCounter = 0;

	/// parse argument
	argumentParser(argc, argv,fileExt,fileName, camCalibFile,optionFile,initCounter);

	input imgIn(fileExt,initCounter);

	/// Image at t = k-1
	cv::Mat imgR0,imgL0;

	/// get image at t = 0
	if(!imgIn.update(imgL0,imgR0))
	{
		std::cout<<"Error reading image input\n";
		return false;
	}

	int Fr =0;
	std::vector<cv::Point2f> vctLPt0, vctRPt0;
	bool paused = false;

	while(true) {

		cv::Mat imgLt, imgRt;

		if(!imgIn.update(imgLt,imgRt))
		{
			std::cout<<"End of image sequence\n";
			break;
		}

		cv::Mat dispImgL = imgLt.clone();
		cv::Mat dispImgR = imgRt.clone();

		std::vector<cv::Point2f> vctLPt1, vctRPt1;

		if(Fr % 10 == 0){
			featMng.extratFeature(imgLt,vctLPt1);
//			featMng.trackFeature(imgLt,imgRt,vctLPt1,vctRPt1);
		}
		else{
			featMng.trackFeature(imgL0,imgLt,vctLPt0,vctLPt1);
//			featMng.trackFeature(imgR0,imgRt,vctRPt0,vctRPt1);
		}

		featMng.trackFeature(imgLt,imgRt,vctLPt1,vctRPt1);

		for(unsigned int i=0 ; i < vctLPt1.size(); ++i) {
			cv::circle(dispImgL,vctLPt1[i],3,cv::Scalar(0,255,255),1);
		}

		for(unsigned int i=0 ; i < vctRPt1.size(); ++i) {
			cv::circle(dispImgR,vctRPt1[i],3,cv::Scalar(0,255,255),1);
		}

		cv::vconcat(dispImgL,dispImgR,dispImgL);

		cv::imshow("S",dispImgL);

		int key = cv::waitKey(paused?0:1);

		if(key == 'p'){
			paused = (paused?false:true);
		}

		Fr ++;

		imgL0 = imgLt.clone();
		imgR0 = imgRt.clone();

		vctLPt1.swap(vctLPt0);
		vctRPt1.swap(vctRPt0);

	}



	return 0;
}
