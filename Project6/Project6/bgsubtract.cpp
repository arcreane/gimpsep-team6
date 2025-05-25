#include "bgsubtract.hpp"
#include "img_io.hpp" // Though not directly used for load/save, it's part of the project structure
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include <string>
#include <vector> // For argument parsing

namespace bgsubtract {
    void print_bgsubtract_usage() {
        std::cerr << "Usage: mini-gimp bgsubtract [options] <input_video_path> <output_video_path>" << std::endl;
        std::cerr << "Options:" << std::endl;
        std::cerr << "  --varthresh <value>   Set MOG2 variance threshold (default 16.0). Lower is more sensitive." << std::endl;
        std::cerr << "  --history <value>     Set MOG2 history length (default 500)." << std::endl;
        std::cerr << "  --noshadows           If set, detected shadows will not be part of the foreground output." << std::endl;
        std::cerr << "                        (MOG2 detects shadows by default)." << std::endl;
    }

    int run(int argc, char** argv) {
        // Default parameters
        double varThreshold = 16.0;
        int history = 500;
        bool detectShadows = true; // MOG2 default
        bool keepOnlyPureForeground = false;
        std::string input_video_path = "";
        std::string output_video_path = "";

        // Argument parsing
        std::vector<std::string> args(argv + 2, argv + argc);
        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "--varthresh") {
                if (i + 1 < args.size()) {
                    try {
                        varThreshold = std::stod(args[++i]);
                    } catch (const std::exception& e) {
                        std::cerr << "Error: Invalid value for --varthresh." << std::endl;
                        print_bgsubtract_usage();
                        return 1;
                    }
                } else {
                    std::cerr << "Error: --varthresh option requires a value." << std::endl;
                    print_bgsubtract_usage();
                    return 1;
                }
            } else if (args[i] == "--history") {
                if (i + 1 < args.size()) {
                    try {
                        history = std::stoi(args[++i]);
                    } catch (const std::exception& e) {
                        std::cerr << "Error: Invalid value for --history." << std::endl;
                        print_bgsubtract_usage();
                        return 1;
                    }
                } else {
                    std::cerr << "Error: --history option requires a value." << std::endl;
                    print_bgsubtract_usage();
                    return 1;
                }
            } else if (args[i] == "--noshadows") {
                keepOnlyPureForeground = true;
            } else if (input_video_path.empty()) {
                input_video_path = args[i];
            } else if (output_video_path.empty()) {
                output_video_path = args[i];
            } else {
                std::cerr << "Error: Unknown or misplaced argument: " << args[i] << std::endl;
                print_bgsubtract_usage();
                return 1;
            }
        }

        if (input_video_path.empty() || output_video_path.empty()) {
            std::cerr << "Error: Input and output video paths are required." << std::endl;
            print_bgsubtract_usage();
            return 1;
        }

        cv::VideoCapture cap(input_video_path);
        if (!cap.isOpened()) {
            std::cerr << "Error: Cannot open input video: " << input_video_path << std::endl;
            return 1;
        }

        // Get video properties for the writer
        int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        double fps = cap.get(cv::CAP_PROP_FPS);
        
        std::string out_avi_path = output_video_path;
        if (output_video_path.length() < 4 || output_video_path.substr(output_video_path.length() - 4) != ".avi") {
            out_avi_path = output_video_path + ".avi";
            std::cout << "Info: Output will be saved as AVI. Forcing .avi extension: " << out_avi_path << std::endl;
        }
        cv::VideoWriter video_writer(out_avi_path, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(frame_width, frame_height));
        if (!video_writer.isOpened()) {
            std::cerr << "Error: Cannot create output video writer for: " << out_avi_path << std::endl;
            return 1;
        }

        cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2 = cv::createBackgroundSubtractorMOG2(history, varThreshold, detectShadows);

        cv::Mat frame, fgMask, processedFgMask, foreground_frame;
        int frame_count = 0;
        std::cout << "Processing video with varThreshold=" << varThreshold << ", history=" << history 
                  << ", detectShadows=" << (detectShadows ? "true" : "false") 
                  << ", keepOnlyPureForeground=" << (keepOnlyPureForeground ? "true" : "false") << std::endl;
        std::cout << "Press ESC to stop early (if a window with cv::waitKey is active)." << std::endl;

        while (true) {
            cap >> frame;
            if (frame.empty()) {
                break;
            }

            pMOG2->apply(frame, fgMask);
            processedFgMask = fgMask.clone(); // Work on a copy

            if (detectShadows && keepOnlyPureForeground) {
                // MOG2 marks shadows as 127, foreground as 255. We only want 255.
                cv::threshold(fgMask, processedFgMask, 254, 255, cv::THRESH_BINARY);
            }

            cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
            cv::morphologyEx(processedFgMask, processedFgMask, cv::MORPH_OPEN, kernel);
        

            foreground_frame = cv::Mat::zeros(frame.size(), frame.type());
            frame.copyTo(foreground_frame, processedFgMask); // Use the processed mask

            video_writer.write(foreground_frame);

            frame_count++;
            if (frame_count % 100 == 0) {
                std::cout << "Processed " << frame_count << " frames." << std::endl;
            }
        }

        std::cout << "Finished processing. Output video saved to: " << out_avi_path << std::endl;
        cap.release();
        video_writer.release();
        

        return 0;
    }
} // namespace bgsubtract 