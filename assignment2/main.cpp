/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob
 * Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

std::string kYourName = "Crystal Rodgers";  // Don't forget to change this!

struct Initials {
  char first;
  char last;
  Initials(char f = '\0', char l = '\0') : first(f), last(l) {}
  bool operator==(const Initials& other) const {
    return first == other.first && last == other.last;
  }
};

/*
 */
Initials get_name_initials(const std::string& name) {
  Initials initials;
  if (name.empty()) {
    return initials;
  }
  initials.first = std::toupper(name[0]);
  size_t space_pos = name.find(' ');
  if (space_pos != std::string::npos && space_pos + 1 < name.length()) {
    initials.last = std::toupper(name[space_pos + 1]);
  } else {
    initials.last = '\0';
  }
  return initials;
}

/**
 * Takes in a file name and returns a set containing all of the applicant names
 * as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the
 * function below it) to use a `std::unordered_set` instead. If you do so, make
 * sure to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::ifstream students_file(filename);
  std::set<std::string> students;
  std::string name;
  while (std::getline(students_file, name)) {
    students.insert(name);
  }
  // std::cout << "Students in set:" << std::endl;
  // for (const std::string& student : students) {
  //   std::cout << student << std::endl;
  // }
  // std::cout << "------------------" << std::endl;
  return students;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as
 * this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name,
                                            std::set<std::string>& students) {
  std::queue<const std::string*> matches;
  Initials target_initials = get_name_initials(name);
  for (const std::string& student_name : students) {
    Initials student_initials = get_name_initials(student_name);
    // std::cout << "Checking student: " << student_name
    //           << ", Initials: " << student_initials.first
    //           << student_initials.last;
    if (student_initials == target_initials) {
      matches.push(&student_name);
      // std::cout << "Initials: " << student_initials.first
      //           << student_initials.last << std::endl;
    }
  }
  // std::cout << "Target initials: " << target_initials.first
  //           << target_initials.last << std::endl;
  // std::cout << "------------------" << std::endl;
  std::cout << "Matches found: " << matches.size() << std::endl;
  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true
 * match!
 *
 * You can implement this function however you'd like, but try to do something a
 * bit more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.empty()) {
    return "NO MATCHES FOUND.";
  }

  std::vector<const std::string*> match_list;
  while (!matches.empty()) {
    match_list.push_back(matches.front());
    matches.pop();
  }

  if (match_list.empty()) {
    return "NO MATCHES FOUND.";
  }
  // 随机选择一个匹配项
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, match_list.size() - 1);
  int random_index = distrib(gen);
  const std::string* match_ptr = match_list[random_index];
  return *match_ptr;
}

/**
 * Takes in a file name and returns a set containing all of the applicant names
 * as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the
 * function below it) to use a `std::unordered_set` instead. If you do so, make
 * sure to also change the corresponding functions in `utils.h`.
 */
std::unordered_set<std::string> get_applicants_unordered(std::string filename) {
  std::ifstream students_file(filename);
  std::unordered_set<std::string> students;
  std::string name;
  while (std::getline(students_file, name)) {
    students.insert(name);
  }
  return students;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
