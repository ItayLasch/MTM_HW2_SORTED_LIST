#ifndef EXAM_DETAILS_H
#define EXAM_DETAILS_H

#include <cstdio> 
#include <cstdlib>
#include <cmath>

#include <iostream>
namespace mtm
{
    static const std::string empty_link = "";
    class ExamDetails
    {
        int course_id, month, day, duration;
        double hour;   
        std::string link_to_zoom;

    public:
        /**
         * @brief Constructs a new Exam with it's details according to the input arguments.
         * @param course_id - Course's Id
         * @param month - Course's exam month
         * @param day - Course's exam day
         * @param hour - Course's exam start hour
         * @param duration - Course's exam duration
         * @param link_to_zoom - Course's exam zoom link
         */
        ExamDetails(const int course_id, const int month, const int day, const double hour,
                    const int duration, const std::string link_to_zoom = empty_link);

        /**
        * Copy Constractor - default function.
        * @brief Constructs a copy of the exam that given as parameter.
        * @param exam_detailes - The exam to make copy of himself.
        */
        ExamDetails(const ExamDetails &exam_details) = default;
        /**
        * destractur - default function.
        * @brief delete the Exam and all the data he contains.
        */
        ~ExamDetails() = default;

        /**
         * @brief Constructs a specific exam with mtm course details.
         * @return An exam with mtm course details.
         */
        static ExamDetails makeMatamExam();

        /**
        * operator= - default function.
        * @brief delelt the existing exam and constructs a copy of the exam that given as parameter.
        * @param exam_details - The exam to make copy of himself.
        */
        ExamDetails &operator=(const ExamDetails &exam_details) = default;

        /**
         * operator - subtructs the days between to exams, this and other_exam.
         * @param other_exam - the other exam.
         * @return the difference in days between two exams, this and other_exam.
         */
        int operator-(const ExamDetails &other_exam) const;


        /**
         * @brief checks if this exam is scheduled before other_exam.
         * @param other_exam - exam to compare dates with.
         * @return true - if this exam is happening before the other, false - otherwise.
         */
        bool operator<(const ExamDetails &other_exam) const;


        /**
         * @brief Creates a fromat of output which displays the exam details.
         * @param os - ostream element which we insert the output into.
         * @param exam_details - exam we want to print out.
         * @return os with the output we created in it.
         */
        friend std::ostream &operator<<(std::ostream &os, const ExamDetails &exam_details);

        /**
         * getLink  
         * @return Exam's zoom link.
         */
        std::string getLink() const;
        
        /**
         * setLink - update the Exam link with @param new_link
         * @param new_link - the new zoom link.
         * @return void.
         */
        void setLink(const std::string new_link);
        
        
        class InvalidDateException
        {
        };
        class InvalidTimeException
        {
        };
        class InvalidArgsException
        {
        };
    };
}
#endif