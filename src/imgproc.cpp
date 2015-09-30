#include <imgproc.hpp>

// Ехали медведи, на велосипеде

extern "C"
struct TensorWrapper getGaussianKernel(int ksize, double sigma, int ktype)
{
    return TensorWrapper(
            cv::getGaussianKernel(ksize, sigma, ktype));
}

extern "C"
struct MultipleTensorWrapper getDerivKernels(
        int dx, int dy, int ksize,
        bool normalize, int ktype)
{
    std::vector<cv::Mat> output(2);

    cv::getDerivKernels(
            output[0], output[1],
            dx, dy, ksize, normalize, ktype);

    return MultipleTensorWrapper(output);
}

extern "C"
struct TensorWrapper getGaborKernel(int ksize_rows, int ksize_cols, double sigma, double theta,
                                    double lambd, double gamma, double psi, int ktype)
{
    return TensorWrapper(
            cv::getGaborKernel(
                    cv::Size(ksize_rows, ksize_cols), sigma, theta, lambd, gamma, psi, ktype));
}

extern "C"
struct TensorWrapper getStructuringElement(int shape, int ksize_rows, int ksize_cols,
                                           int anchor_x, int anchor_y)
{
    return TensorWrapper(
            cv::getStructuringElement(
                    shape, cv::Size(ksize_rows, ksize_cols), cv::Point(anchor_x, anchor_y)));
}

extern "C"
struct TensorWrapper medianBlur(struct TensorWrapper src, struct TensorWrapper dst, int ksize)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::medianBlur(src.toMat(), retval, ksize);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::medianBlur(source, source, ksize);
    } else {
        cv::medianBlur(src.toMat(), dst.toMat(), ksize);
    }
    return dst;
}

extern "C"
struct TensorWrapper GaussianBlur(struct TensorWrapper src, struct TensorWrapper dst,
                                  int ksize_x, int ksize_y, double sigmaX,
                                  double sigmaY, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::GaussianBlur(
                src.toMat(), retval, cv::Size(ksize_x, ksize_y), sigmaX, sigmaY, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::GaussianBlur(
                source, source, cv::Size(ksize_x, ksize_y), sigmaX, sigmaY, borderType);
    } else {
        cv::GaussianBlur(
                src.toMat(), dst.toMat(), cv::Size(ksize_x, ksize_y), sigmaX, sigmaY, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper bilateralFilter(struct TensorWrapper src, struct TensorWrapper dst, int d,
                                     double sigmaColor, double sigmaSpace,
                                     int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::bilateralFilter(
                src.toMat(), retval, d, sigmaColor, sigmaSpace, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::bilateralFilter(
                source, source, d, sigmaColor, sigmaSpace, borderType);
    } else {
        cv::bilateralFilter(
                src.toMat(), dst.toMat(), d, sigmaColor, sigmaSpace, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper boxFilter(
        struct TensorWrapper src, struct TensorWrapper dst, int ddepth,
        int ksize_x, int ksize_y, int anchor_x, int anchor_y,
        bool normalize, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::boxFilter(
                src.toMat(), retval, ddepth, cv::Size(ksize_x, ksize_y),
                cv::Point(anchor_x, anchor_y), normalize, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::boxFilter(
                source, source, ddepth, cv::Size(ksize_x, ksize_y),
                cv::Point(anchor_x, anchor_y), normalize, borderType);
    } else {
        cv::boxFilter(
                src.toMat(), dst.toMat(), ddepth, cv::Size(ksize_x, ksize_y),
                cv::Point(anchor_x, anchor_y), normalize, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper sqrBoxFilter(
        struct TensorWrapper src, struct TensorWrapper dst, int ddepth,
        int ksize_x, int ksize_y, int anchor_x, int anchor_y,
        bool normalize, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::sqrBoxFilter(src.toMat(), retval, ddepth,
                cv::Point(ksize_x, ksize_y), cv::Point(anchor_x, anchor_y),
                normalize, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::sqrBoxFilter(source, source, ddepth, cv::Point(ksize_x, ksize_y), cv::Point(anchor_x, anchor_y),
                normalize, borderType);
    } else {
        cv::sqrBoxFilter(src.toMat(), dst.toMat(), ddepth, cv::Point(ksize_x, ksize_y), cv::Point(anchor_x, anchor_y),
                normalize, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper blur(
        struct TensorWrapper src, struct TensorWrapper dst,
        int ksize_x, int ksize_y, int anchor_x, int anchor_y, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::blur(src.toMat(), retval, cv::Point(ksize_x, ksize_y), cv::Point(anchor_x, anchor_y), borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::blur(source, source, cv::Point(ksize_x, ksize_y), cv::Point(anchor_x, anchor_y), borderType);
    } else {
        cv::blur(src.toMat(), dst.toMat(), cv::Point(ksize_x, ksize_y), cv::Point(anchor_x, anchor_y), borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper filter2D(
        struct TensorWrapper src, struct TensorWrapper dst, int ddepth,
        struct TensorWrapper kernel, int anchor_x, int anchor_y,
        double delta, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::filter2D(src.toMat(), retval, ddepth,
        kernel.toMat(), cv::Point(anchor_x, anchor_y),
        delta, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::filter2D(source, source, ddepth,
        kernel.toMat(), cv::Point(anchor_x, anchor_y),
        delta, borderType);
    } else {
        cv::filter2D(src.toMat(), dst.toMat(), ddepth,
        kernel.toMat(), cv::Point(anchor_x, anchor_y),
        delta, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper sepFilter2D(
        struct TensorWrapper src, struct TensorWrapper dst, int ddepth,
        struct TensorWrapper kernelX,struct TensorWrapper kernelY,
        int anchor_x, int anchor_y, double delta, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::sepFilter2D(src.toMat(), retval, ddepth,
        kernelX.toMat(),kernelY.toMat(),
        cv::Point(anchor_x, anchor_y), delta, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::sepFilter2D(source, source, ddepth,
        kernelX.toMat(),kernelY.toMat(),
        cv::Point(anchor_x, anchor_y), delta, borderType);
    } else {
        cv::sepFilter2D(src.toMat(), dst.toMat(), ddepth,
        kernelX.toMat(),kernelY.toMat(),
        cv::Point(anchor_x, anchor_y), delta, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper Sobel(
        struct TensorWrapper src, struct TensorWrapper dst, int ddepth,
        int dx, int dy, int ksize, double scale, double delta, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::Sobel(src.toMat(), retval, ddepth,
                dx, dy, ksize, scale, delta, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::Sobel(source, source, ddepth,
                dx, dy, ksize, scale, delta, borderType);
    } else {
        cv::Sobel(src.toMat(), dst.toMat(), ddepth,
                dx, dy, ksize, scale, delta, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper Scharr(
        struct TensorWrapper src, struct TensorWrapper dst, int ddepth,
        int dx, int dy, double scale, double delta, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::Scharr(src.toMat(), retval, ddepth,
                dx, dy, scale, delta, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::Scharr(source, source, ddepth,
                dx, dy, scale, delta, borderType);
    } else {
        cv::Scharr(src.toMat(), dst.toMat(), ddepth,
                dx, dy, scale, delta, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper Laplacian(
        struct TensorWrapper src, struct TensorWrapper dst, int ddepth,
        int ksize, double scale, double delta, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::Laplacian(src.toMat(), retval, ddepth,
                ksize, scale, delta, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::Laplacian(source, source, ddepth,
                ksize, scale, delta, borderType);
    } else {
        cv::Laplacian(src.toMat(), dst.toMat(), ddepth,
                ksize, scale, delta, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper Canny(
        struct TensorWrapper image, struct TensorWrapper edges,
        double threshold1, double threshold2, int apertureSize, bool L2gradient)
{
    if (edges.isNull()) {
        cv::Mat retval;
        cv::Canny(image.toMat(), retval, threshold1, threshold2, apertureSize, L2gradient);
        return TensorWrapper(retval);
    } else if (edges.tensorPtr == image.tensorPtr) {
        // in-place 
        cv::Mat source = image.toMat();
        cv::Canny(source, source, threshold1, threshold2, apertureSize, L2gradient);
    } else {
        cv::Canny(image.toMat(), edges.toMat(), threshold1, threshold2, apertureSize, L2gradient);
    }
    return edges;
}

extern "C"
struct TensorWrapper cornerMinEigenVal(
        struct TensorWrapper src, struct TensorWrapper dst,
        int blockSize, int ksize, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::cornerMinEigenVal(src.toMat(), retval, blockSize, ksize, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        std::cout << "inplace" << std::endl;
        cv::Mat source = src.toMat();
        cv::cornerMinEigenVal(source, source, blockSize, ksize, borderType);
    } else {
        cv::cornerMinEigenVal(src.toMat(), dst.toMat(), blockSize, ksize, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper cornerHarris(
        struct TensorWrapper src, struct TensorWrapper dst, int blockSize,
        int ksize, double k, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::cornerHarris(src.toMat(), retval, blockSize,
                ksize, k, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::cornerHarris(source, source, blockSize,
                ksize, k, borderType);
    } else {
        cv::cornerHarris(src.toMat(), dst.toMat(), blockSize,
                ksize, k, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper cornerEigenValsAndVecs(
        struct TensorWrapper src, struct TensorWrapper dst,
        int blockSize, int ksize, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::cornerEigenValsAndVecs(src.toMat(), retval, blockSize, ksize, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::cornerEigenValsAndVecs(source, source, blockSize, ksize, borderType);
    } else {
        cv::cornerEigenValsAndVecs(src.toMat(), dst.toMat(), blockSize, ksize, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper preCornerDetect(
        struct TensorWrapper src, struct TensorWrapper dst, int ksize, int borderType)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::preCornerDetect(src.toMat(), retval, ksize, borderType);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::preCornerDetect(source, source, ksize, borderType);
    } else {
        cv::preCornerDetect(src.toMat(), dst.toMat(), ksize, borderType);
    }
    return dst;
}

extern "C"
struct TensorWrapper HoughLines(
        struct TensorWrapper image,
        double rho, double theta, int threshold, double srn, double stn,
        double min_theta, double max_theta)
{
    cv::Mat retval;
    cv::HoughLines(image.toMat(), retval, theta, threshold, srn, stn,
                min_theta, max_theta);
    return TensorWrapper(retval);
}

extern "C"
struct TensorWrapper HoughLinesP(
        struct TensorWrapper image, double rho,
        double theta, int threshold, double minLineLength, double maxLineGap)
{
    cv::Mat retval;
    cv::HoughLinesP(image.toMat(), retval, rho,
                theta, threshold, minLineLength, maxLineGap);
    return TensorWrapper(retval);
}

extern "C"
struct TensorWrapper HoughCircles(
        struct TensorWrapper image,
        int method, double dp, double minDist, double param1, double param2,
        int minRadius, int maxRadius)
{
    cv::Mat retval;
    cv::HoughCircles(image.toMat(), retval, method, dp, minDist, param1, param2,
            minRadius, maxRadius);
    return TensorWrapper(retval);
}

extern "C"
void cornerSubPix(
        struct TensorWrapper image, struct TensorWrapper corners,
        int winSize_x, int winSize_y, int zeroZone_x, int zeroZone_y,
        struct TermCriteriaWrapper criteria)
{
    cv::cornerSubPix(image.toMat(), corners.toMat(), cv::Size(winSize_x, winSize_y),
                     cv::Size(zeroZone_x, zeroZone_y), criteria.toCV());
}

extern "C"
struct TensorWrapper goodFeaturesToTrack(
        struct TensorWrapper image,
        int maxCorners, double qualityLevel, double minDistance,
        struct TensorWrapper mask, int blockSize, bool useHarrisDetector, double k)
{
    cv::Mat retval;
    cv::goodFeaturesToTrack(image.toMat(), retval, maxCorners, qualityLevel, minDistance,
        mask.tensorPtr ? mask.toMat() : cv::noArray(), blockSize, useHarrisDetector, k);
    return retval;
}

extern "C"
struct TensorWrapper erode(
        struct TensorWrapper src, struct TensorWrapper dst,
        struct TensorWrapper kernel, int anchor_x, int anchor_y,
        int iterations, int borderType, struct ScalarWrapper borderValue)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::erode(src.toMat(), retval, kernel.toMat(), cv::Point(anchor_x, anchor_y), iterations,
                  borderType, isnan(borderValue.v0) ? cv::morphologyDefaultBorderValue() : borderValue.toCV());
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::erode(source, source, kernel.toMat(), cv::Point(anchor_x, anchor_y), iterations,
                  borderType, isnan(borderValue.v0) ? cv::morphologyDefaultBorderValue() : borderValue.toCV());
    } else {
        cv::erode(src.toMat(), dst.toMat(), kernel.toMat(), cv::Point(anchor_x, anchor_y), iterations,
                  borderType, isnan(borderValue.v0) ? cv::morphologyDefaultBorderValue() : borderValue.toCV());
    }
    return dst;
}

extern "C"
struct TensorWrapper dilate(
        struct TensorWrapper src, struct TensorWrapper dst,
        struct TensorWrapper kernel, int anchor_x, int anchor_y,
        int iterations, int borderType, struct ScalarWrapper borderValue)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::dilate(src.toMat(), retval, kernel.toMat(), cv::Point(anchor_x, anchor_y), iterations,
                  borderType, isnan(borderValue.v0) ? cv::morphologyDefaultBorderValue() : borderValue.toCV());
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::dilate(source, source, kernel.toMat(), cv::Point(anchor_x, anchor_y), iterations,
                  borderType, isnan(borderValue.v0) ? cv::morphologyDefaultBorderValue() : borderValue.toCV());
    } else {
        cv::dilate(src.toMat(), dst.toMat(), kernel.toMat(), cv::Point(anchor_x, anchor_y), iterations,
                  borderType, isnan(borderValue.v0) ? cv::morphologyDefaultBorderValue() : borderValue.toCV());
    }
    return dst;
}

extern "C"
struct TensorWrapper morphologyEx(
        struct TensorWrapper src, struct TensorWrapper dst,
        int op, struct TensorWrapper kernel, int anchor_x, int anchor_y,
        int iterations, int borderType, struct ScalarWrapper borderValue)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::morphologyEx(src.toMat(), retval, op, kernel.toMat(), cv::Point(anchor_x, anchor_y), iterations,
                   borderType, isnan(borderValue.v0) ? cv::morphologyDefaultBorderValue() : borderValue.toCV());
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::morphologyEx(source, source, op, kernel.toMat(), cv::Point(anchor_x, anchor_y), iterations,
                   borderType, isnan(borderValue.v0) ? cv::morphologyDefaultBorderValue() : borderValue.toCV());
    } else {
        cv::morphologyEx(src.toMat(), dst.toMat(), op, kernel.toMat(), cv::Point(anchor_x, anchor_y), iterations,
                   borderType, isnan(borderValue.v0) ? cv::morphologyDefaultBorderValue() : borderValue.toCV());
    }
    return dst;
}

extern "C"
struct TensorWrapper resize(
        struct TensorWrapper src, struct TensorWrapper dst,
        int dsize_x, int dsize_y, double fx, double fy,
        int interpolation)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::resize(src.toMat(), retval, cv::Size(dsize_x, dsize_y), fx, fy, interpolation);
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::resize(source, source, cv::Size(dsize_x, dsize_y), fx, fy, interpolation);
    } else {
        cv::resize(src.toMat(), dst.toMat(), cv::Size(dsize_x, dsize_y), fx, fy, interpolation);
    }
    return dst;
}

extern "C"
struct TensorWrapper warpAffine(
        struct TensorWrapper src, struct TensorWrapper dst,
        struct TensorWrapper M, int dsize_x, int dsize_y,
        int flags, int borderMode, struct ScalarWrapper borderValue)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::warpAffine(src.toMat(), retval, M.toMat(), cv::Size(dsize_x, dsize_y), flags, borderMode, borderValue.toCV());
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::warpAffine(source, source, M.toMat(), cv::Size(dsize_x, dsize_y), flags, borderMode, borderValue.toCV());
    } else {
        cv::warpAffine(src.toMat(), dst.toMat(), M.toMat(), cv::Size(dsize_x, dsize_y), flags, borderMode, borderValue.toCV());
    }
    return dst;
}

extern "C"
struct TensorWrapper warpPerspective(
        struct TensorWrapper src, struct TensorWrapper dst,
        struct TensorWrapper M, int dsize_x, int dsize_y,
        int flags, int borderMode, struct ScalarWrapper borderValue)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::warpPerspective(src.toMat(), retval, M.toMat(), cv::Size(dsize_x, dsize_y), flags, borderMode, borderValue.toCV());
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::warpPerspective(source, source, M.toMat(), cv::Size(dsize_x, dsize_y), flags, borderMode, borderValue.toCV());
    } else {
        cv::warpPerspective(src.toMat(), dst.toMat(), M.toMat(), cv::Size(dsize_x, dsize_y), flags, borderMode, borderValue.toCV());
    }
    return dst;
}

extern "C"
struct TensorWrapper remap(
        struct TensorWrapper src, struct TensorWrapper dst,
        struct TensorWrapper map1, struct TensorWrapper map2,
        int interpolation, int borderMode, struct ScalarWrapper borderValue)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::remap(src.toMat(), retval, map1.toMat(), map2.toMat(), interpolation, borderMode, borderValue.toCV());
        return TensorWrapper(retval);
    } else if (dst.tensorPtr == src.tensorPtr) {
        // in-place
        cv::Mat source = src.toMat();
        cv::remap(source, source, map1.toMat(), map2.toMat(), interpolation, borderMode, borderValue.toCV());
    } else {
        cv::remap(src.toMat(), dst.toMat(), map1.toMat(), map2.toMat(), interpolation, borderMode, borderValue.toCV());
    }
    return dst;
}

extern "C"
struct MultipleTensorWrapper convertMaps(
        struct TensorWrapper map1, struct TensorWrapper map2,
        struct TensorWrapper dstmap1, struct TensorWrapper dstmap2,
        int dstmap1type, bool nninterpolation)
{
    if (dstmap1.isNull() and dstmap2.isNull()) {
        // output to retval
        std::vector<cv::Mat> retval(2);
        cv::convertMaps(map1.toMat(), map2.toMat(), retval[0], retval[1], dstmap1type, nninterpolation);
        return MultipleTensorWrapper(retval);
    }
    if (!dstmap1.isNull() and !dstmap2.isNull()) {
        // try to output to the given Tensors
        cv::convertMaps(map1.toMat(), map2.toMat(), dstmap1.toMat(), dstmap2.toMat(), dstmap1type, nninterpolation);
        return MultipleTensorWrapper();
    }
    THError("convertMaps: please specify either both or none of the dstmaps");
}

extern "C"
struct TensorWrapper getRotationMatrix2D(
        float center_x, float center_y, double angle, double scale)
{
    return TensorWrapper(cv::getRotationMatrix2D(cv::Point2f(center_x, center_y), angle, scale));
}

extern "C"
struct TensorWrapper invertAffineTransform(
        struct TensorWrapper M, struct TensorWrapper iM)
{
    if (iM.isNull()) {
        cv::Mat retval;
        cv::invertAffineTransform(M.toMat(), retval);
        return TensorWrapper(retval);
    } else if (iM.tensorPtr == M.tensorPtr) {
        // in-place
        cv::Mat source = M.toMat();
        cv::invertAffineTransform(source, source);
    } else {
        cv::invertAffineTransform(M.toMat(), iM.toMat());
    }
    return iM;
}

extern "C" struct TensorWrapper getPerspectiveTransform(
        struct TensorWrapper src, struct TensorWrapper dst)
{
    return TensorWrapper(cv::getPerspectiveTransform(src.toMat(), dst.toMat()));
}

extern "C" struct TensorWrapper getAffineTransform(
        struct TensorWrapper src, struct TensorWrapper dst)
{
    return TensorWrapper(cv::getAffineTransform(src.toMat(), dst.toMat()));
}

extern "C" struct TensorWrapper getRectSubPix(
        struct TensorWrapper image, int patchSize_x, int patchsize_y,
        float center_x, float center_y, struct TensorWrapper patch, int patchType)
{
    if (patch.isNull()) {
        cv::Mat retval;
        cv::getRectSubPix(image.toMat(), cv::Size(patchSize_x, patchsize_y),
                          cv::Point2f(center_x, center_y), retval, patchType);
        return TensorWrapper(retval);
    } else if (image.tensorPtr == patch.tensorPtr) {
        // in-place
        THError("In-place isn't possible");
    } else {
        cv::getRectSubPix(image.toMat(), cv::Size(patchSize_x, patchsize_y),
                          cv::Point2f(center_x, center_y), patch.toMat(), patchType);
    }
    return patch;
}

extern "C" 
struct TensorWrapper logPolar(
        struct TensorWrapper src, struct TensorWrapper dst,
        float center_x, float center_y, double M, int flags)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::logPolar(src.toMat(), retval, cv::Point2f(center_x, center_y), M, flags);
        return TensorWrapper(retval);
    } else if (src.tensorPtr == dst.tensorPtr) {
        // in-place
        THError("In-place isn't possible");
    } else {
        cv::logPolar(src.toMat(), dst.toMat(), cv::Point2f(center_x, center_y), M, flags);
    }
    return dst;
}

extern "C"
struct TensorWrapper linearPolar(
        struct TensorWrapper src, struct TensorWrapper dst,
        float center_x, float center_y, double maxRadius, int flags)
{
    if (dst.isNull()) {
        cv::Mat retval;
        cv::linearPolar(src.toMat(), retval, cv::Point2f(center_x, center_y), maxRadius, flags);
        return TensorWrapper(retval);
    } else if (src.tensorPtr == dst.tensorPtr) {
        // in-place
        THError("In-place isn't possible");
    } else {
        cv::linearPolar(src.toMat(), dst.toMat(), cv::Point2f(center_x, center_y), maxRadius, flags);
    }
    return dst;
}

extern "C" 
struct TensorWrapper integral(
        struct TensorWrapper src, struct TensorWrapper sum, int sdepth)
{
    if (sum.isNull()) {
        cv::Mat retval;
        cv::integral(src.toMat(), retval, sdepth);
        return TensorWrapper(retval);
    } else if (sum.tensorPtr == src.tensorPtr) {
        // in-place 
        cv::Mat source = src.toMat();
        cv::integral(source, source, sdepth);
    } else {
        cv::integral(src.toMat(), sum.toMat(), sdepth);
    }
    return sum;
}

extern "C" struct MultipleTensorWrapper integralN(
        struct TensorWrapper src, struct MultipleTensorWrapper sums, int sdepth, int sqdepth)
{
    // sums.size == 2 or 3
    std::vector<cv::Mat> retval(sums.size);

    for (short i = 0; i < sums.size; ++i) {
        if (!sums.tensors[i].isNull()) {
            retval[i] = sums.tensors[i].toMat();
        }
    }
    cv::integral(src.toMat(), retval[0], retval[1], sdepth, sqdepth);

    return MultipleTensorWrapper(retval);
}

extern "C"
void accumulate(
        struct TensorWrapper src, struct TensorWrapper dst,
        struct TensorWrapper mask)
{
    cv::accumulate(src.toMat(), dst.toMat(), mask.isNull() ? cv::noArray() : mask.toMat());
}

extern "C"
void accumulateSquare(
        struct TensorWrapper src, struct TensorWrapper dst,
        struct TensorWrapper mask)
{
    cv::accumulateSquare(src.toMat(), dst.toMat(), mask.isNull() ? cv::noArray() : mask.toMat());
}

extern "C"
void accumulateProduct(
        struct TensorWrapper src1, struct TensorWrapper src2,
        struct TensorWrapper dst, struct TensorWrapper mask)
{
    cv::accumulateProduct(src1.toMat(), src2.toMat(), dst.toMat(), mask.isNull() ? cv::noArray() : mask.toMat());
}

extern "C"
void accumulateWeighted(
        struct TensorWrapper src, struct TensorWrapper dst,
        double alpha, struct TensorWrapper mask)
{
    cv::accumulateWeighted(src.toMat(), dst.toMat(), alpha, mask.isNull() ? cv::noArray() : mask.toMat());
}

extern "C"
struct Vec3d phaseCorrelate(
        struct TensorWrapper src1, struct TensorWrapper src2,
        struct TensorWrapper window)
{
    Vec3d retval;
    cv::Point2d result =
            cv::phaseCorrelate(src1.toMat(), src2.toMat(),
                               window.isNull() ? cv::noArray() : window.toMat(), &retval.v2);
    retval.v0 = result.x;
    retval.v1 = result.y;
    return retval;
}