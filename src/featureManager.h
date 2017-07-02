/*
 * featureManager.h
 *
 *  Created on: Jun 25, 2017
 *      Author: xwong
 */

#ifndef FEATUREMANAGER_H_
#define FEATUREMANAGER_H_

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/nonfree/nonfree.hpp"


class featureManager {
private:

	std::vector< std::vector<cv::Point2f> > vctFeatureTrack;

	cv::Ptr<cv::ORB> ptrFetureDectector = new cv::ORB(300,1.2,3,30,0,0,cv::ORB::HARRIS_SCORE,30);

public:
	featureManager();

	void extratFeature(cv::Mat img, std::vector<cv::Point2f>& vctFeturePt);

	void trackFeature(cv::Mat img0, cv::Mat img1, std::vector<cv::Point2f>& vctFeturePt0, std::vector<cv::Point2f>& vctFeturePt1,
			cv::Mat R = cv::Mat(), cv::Mat T = cv::Mat(), cv::Mat K = cv::Mat(), cv::Mat Rc = cv::Mat(), cv::Mat Tc = cv::Mat());

	void getFeaturePair(std::vector<cv::Point2f>& vctFeturePt0, std::vector<cv::Point2f>& vctFeturePt1);

	virtual ~featureManager();
};

#endif /* FEATUREMANAGER_H_ */
