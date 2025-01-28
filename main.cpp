#include <fmt/core.h>
#include <stdio.h>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>

typedef std::vector<cv::Point2f> Targets;

enum BotState
{
  IS_SEARCHING,
  IS_HOVERED,
  IS_SELECTED,
  IS_ATTACK,
  IS_PICKUP
};

class Bot
{
public:
  bool is_running = false;
  BotState state;
  Targets targets = {};

  Bot()
  {
  }

  Targets get_targets()
  {
    this->targets = {};
    return this->targets;
  }

  bool is_hovered()
  {
  }
  bool is_selected()
  {
  }

  // Actions

  void search_target() {
    fmt::println("Searching...");
    // if is search.
    this->state = BotState::IS_HOVERED;
  }

  void select_target() {
    this->state = BotState::IS_SELECTED;
  }

  void attack_target() {
    fmt::println("Bot attack!");
    this->state = BotState::IS_ATTACK;
  }

  // Main loop

  void run()
  {
    while (true)
    {
      switch (this->state)
      {
      case BotState::IS_SEARCHING:
        this->search_target();
        break;
      case BotState::IS_HOVERED:
        this->select_target();
        break;
      case BotState::IS_SELECTED:
        this->attack_target();
        break;
      case BotState::IS_ATTACK:
        // check hp...
        break;
      case BotState::IS_PICKUP:
        fmt::println("Bot searching...");
        break;

      default:
        fmt::println("Bot default...");
      }
    }
  }
};

cv::Point2f detect(cv::Mat &img, cv::Mat &templ)
{
  cv::Mat result;

  // Methods

  // cv::TM_SQDIFF;
  // cv::TM_SQDIFF_NORMED;
  // cv::TM_CCORR;
  // cv::TM_CCORR_NORMED;
  // cv::TM_CCOEFF;
  // cv::TM_CCOEFF_NORMED;

  cv::TemplateMatchModes method = cv::TM_CCOEFF_NORMED;

  int result_cols = img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create(result_rows, result_cols, CV_32FC1);

  matchTemplate(img, templ, result, method);
  fmt::println("{}", result.cols);
  normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

  double minVal, maxVal;
  cv::Point minLoc, maxLoc, matchLoc;

  cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

  matchLoc = (method == cv::TM_SQDIFF || method == cv::TM_SQDIFF_NORMED) ? minLoc : maxLoc;

  cv::Point from = matchLoc;                                                  // x1 y1
  cv::Point to = cv::Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows); // x2 y2

  cv::Point2f center = cv::Point2f((from.x + to.x) / 2, (from.y + to.y) / 2);

  fmt::println("{} : {}", center.x, center.y);

  return center;
}

int main()
{
  cv::Mat img = cv::imread("../img/img.jpg", cv::IMREAD_GRAYSCALE);
  cv::Mat templ = cv::imread("../img/target_hovered.jpg", cv::IMREAD_GRAYSCALE);
  cv::Point2f result = detect(img, templ);
  auto color = cv::Scalar(0, 255, 100);

  cv::circle(img, result, 20, color, 5);

  cv::imshow("img", img);
  cv::waitKey(0);

  return 0;
}