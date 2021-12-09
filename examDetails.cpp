#include "examDetails.h"

namespace mtm
{
    using std::string;
    static const int mtm_course_id = 234124;
    static const int mtm_month = 7;
    static const int mtm_day = 28;
    static const int mtm_exam_duration = 3;
    static constexpr double mtm_exam_start = 13.0;
    static const string mtm_link = "https://tinyurl.com/59hzps6m";
    static const string round_hour = ":00";
    static const string half_hour = ":30";
    static constexpr double epsilon = 0.000001; // pow(10.0,-6.0);
    static const int days_in_month = 30;
    static constexpr double half = 0.5;
    static constexpr double hour_limit = 23.5;
    static const int bigget_month = 12;
    static const int biggest_day = 30;

    /**
     * roundedNum - rounds the number up or down according to to which side it closest to.
     * @param arg - the argument we want to round.
     * @return the rounded number.
     */
    static int roundedNum(double arg)
    {
        double fraction, arg_int_part = 0;
        fraction = std::modf(arg, &arg_int_part);
        if (fraction > 1 - epsilon)
        {
            return (int)arg_int_part + 1;
        }
        return (int)arg_int_part;
    }

    /**
     * checkIsDateValid - Checks if the recieved date is valid 
     * @param month - month input to check
     * @param day - day input to check
     * @return true - if date is valid, false - otherwise
     */
    static bool checkIsDateValid(const int month, const int day)
    {
        if (month > bigget_month || month < 1 || day > biggest_day || day < 1)
        {
            return false;
        }

        return true;
    }

    /**
     * @checkIsHourValid - Checks if the hour input is valid 
     * @param hour - Hour input to check.
     * @return true - if hour is valid according to the rules, false - otherwise
     */
    static bool checkIsHourValid(const double hour)
    {
        int int_part_hour = roundedNum(hour);
        if (hour < -epsilon || hour - hour_limit > epsilon)
        {
            return false;
        }

        if (fabs(hour - int_part_hour - half) > epsilon && fabs(hour - int_part_hour) > epsilon)
        {
            return false;
        }

        return true;
    }

    ExamDetails::ExamDetails(const int course_id, const int month, const int day,
                             const double hour, const int duration, const string link_to_zoom)
    {

        if (checkIsDateValid(month, day) == false)
        {
            throw ExamDetails::InvalidDateException();
        }

        if (checkIsHourValid(hour) == false)
        {
            throw ExamDetails::InvalidTimeException();
        }

        if (duration < 0)
        {
            throw ExamDetails::InvalidArgsException();
        }

        this->course_id = course_id;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->duration = duration;
        this->link_to_zoom = link_to_zoom;
    }

    ExamDetails ExamDetails::makeMatamExam()
    {
        int course_id = mtm_course_id, month = mtm_month, day = mtm_day, duration = mtm_exam_duration;
        double hour = mtm_exam_start;
        string link = mtm_link;
        ExamDetails matam_exam(course_id, month, day, hour, duration, link);

        return matam_exam;
    }

    int ExamDetails::operator-(const ExamDetails &other_exam) const
    {
        int number_of_days = (this->month - other_exam.month) * days_in_month;
        number_of_days += this->day - other_exam.day;
        return number_of_days;
    }

    bool ExamDetails::operator<(const ExamDetails &other_exam) const
    {
        int days_diff = *this - other_exam;
        if (days_diff < 0)
        {
            return true;
        }
        else if (days_diff > 0)
        {
            return false;
        }

        if (this->hour >= other_exam.hour)
        {
            return false;
        }

        if (other_exam.hour - this->hour < epsilon)
        {
            return false;
        }
        return true;
    }

    std::ostream &operator<<(std::ostream &os, const ExamDetails &exam_details)
    {
        string minutes = round_hour;
        double fraction, hour_int_part = 0;
        fraction = std::modf(exam_details.hour, &hour_int_part);
        if (fabs(fraction - half) < epsilon)
        {
            minutes = half_hour;
        }

        os << "Course Number: " << exam_details.course_id << std::endl;
        os << "Time: " << exam_details.day << "." << exam_details.month << " at " << roundedNum(exam_details.hour)
           << minutes << std::endl;
        os << "Duration: " << exam_details.duration << round_hour << std::endl;
        os << "Zoom Link: " << exam_details.link_to_zoom << std::endl;

        return os;
    }

    string ExamDetails::getLink() const
    {
        return this->link_to_zoom;
    }

    void ExamDetails::setLink(const string new_link)
    {
        this->link_to_zoom = new_link;
    }
}
