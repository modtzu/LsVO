/*
 * featureManager.cpp
 *
 *  Created on: Jun 25, 2017
 *      Author: xwong
 */

#include "featureManager.h"

featureManager::featureManager() {
	// TODO Auto-generated constructor stub

}

void featureManager::extratFeature(cv::Mat img,
		std::vector<cv::Point2f>& vctFeturePt) {

	cv::Mat gray;

	if(img.channels()!=1){
		cv::cvtColor(img,gray,cv::COLOR_RGB2GRAY);
	} else {
		gray = img.clone();
	}

	cv::Mat mask = cv::Mat::ones(img.size(),CV_8UC1);

	std::vector<cv::KeyPoint> keyPt;

	ptrFetureDectector->detect(gray,keyPt,mask);

	cv::KeyPoint::convert(keyPt,vctFeturePt);
}

void featureManager::trackFeature(cv::Mat img0, cv::Mat img1, std::vector<cv::Point2f>& vctFeturePt0, std::vector<cv::Point2f>& vctFeturePt1,
		cv::Mat R, cv::Mat T, cv::Mat K,cv::Mat Rc, cv::Mat Tc) {

	std::vector<uchar> status;
	std::vector<float> err;
	int maxLvl = 3;
	cv::TermCriteria termCrit = cv::TermCriteria(cv::TermCriteria::MAX_ITER+cv::TermCriteria::EPS,30,1e-4);
	cv::Size kltSize(21,21);

	cv::calcOpticalFlowPyrLK(img0,img1,vctFeturePt0,vctFeturePt1,status,err,kltSize,maxLvl,termCrit,0,1e-4);

}

void featureManager::getFeaturePair(std::vector<cv::Point2f>& vctFeturePt0,
		std::vector<cv::Point2f>& vctFeturePt1) {
}

featureManager::~featureManager() {
	// TODO Auto-generated destructor stub
}

