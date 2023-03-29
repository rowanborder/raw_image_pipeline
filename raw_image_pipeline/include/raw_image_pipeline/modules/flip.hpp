// Author: Matias Mattamala

#pragma once

#include <opencv2/opencv.hpp>

#ifdef HAS_CUDA
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#endif

namespace raw_image_pipeline {

class FlipModule {
 public:
  FlipModule(bool use_gpu);
  void enable(bool enabled);
  bool enabled() const;

  //-----------------------------------------------------------------------------
  // Getters
  //-----------------------------------------------------------------------------
  cv::Mat getImage() const;

  //-----------------------------------------------------------------------------
  // Main interface
  //-----------------------------------------------------------------------------
  template <typename T>
  bool apply(T& image) {
    if (!enabled_) {
      return false;
    }
    flip(image);
    saveFlippedImage(image);
    return true;
  }

  //-----------------------------------------------------------------------------
  // Helper methods (CPU)
  //-----------------------------------------------------------------------------
 private:
  void flip(cv::Mat& image);
  void saveFlippedImage(cv::Mat& image);

#ifdef HAS_CUDA
  void flip(cv::cuda::GpuMat& image);
  void saveFlippedImage(cv::cuda::GpuMat& image);
#endif

  //-----------------------------------------------------------------------------
  // Variables
  //-----------------------------------------------------------------------------
  bool enabled_;
  bool use_gpu_;
  cv::Mat image_;
};

}  // namespace raw_image_pipeline