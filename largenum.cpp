#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

LargeNum::LargeNum(const string &number) {
  // Storing the string backwards
  // If the string is negative isPositive will become false
  if (number[0] != '-') {
    reverseNum = number;
    reverse(reverseNum.begin(), reverseNum.end());
  } else if (number[1] - '0' == 0) {
    reverseNum = "0";
  } else {
    isPositive = false;
    reverseNum = number;
    reverse(reverseNum.begin(), reverseNum.end());
    reverseNum.pop_back();
  }
}

LargeNum::LargeNum(int anInteger) {
  // Storing the int into a string that is backwards
  //  and storing if the int is positive or negatif
  if (anInteger > 0) {
    reverseNum = to_string(anInteger);
    reverse(reverseNum.begin(), reverseNum.end());
  } else if (anInteger == 0) {
    reverseNum = "0";
  } else {
    isPositive = false;
    reverseNum = to_string(anInteger);
    reverse(reverseNum.begin(), reverseNum.end());
    reverseNum.pop_back();
  }
}

// prints out the number with appropriate commas
ostream &operator<<(ostream &out, const LargeNum &num) {
  int strLength = num.reverseNum.length();
  int remainder = strLength % 3;
  int count = 0;

  // if the number is negative
  if (num.isPositive == 0 && num.reverseNum.length() != 0) {
    out << "-";
  }

  // prints out the first number
  for (int i = strLength - 1; i > strLength - (1 + remainder); i--) {
    out << num.reverseNum[i];
  }

  // prints a comma if the digit has a remainder
  if (remainder != 0 && num.reverseNum.length() > remainder) {
    out << ",";
  }

  // prints the rest of the numbers with comma
  for (int i = strLength - (1 + remainder); i > -1; i--) {
    count++;
    if (count % 4 != 0) {
      out << num.reverseNum[i];
    } else {
      out << ",";
      i++;
    }
  }

  return out;
}

// print out the sum of 2 LargeNum
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  string answer = "";
  int carry = 0;
  string topNum = reverseNum;
  string botNum = rhs.reverseNum;
  reverse(topNum.begin(), topNum.end());
  reverse(botNum.begin(), botNum.end());

  // a + -b == a - b
  //-a + b == b - a
  if (isPositive == 1 && rhs.isPositive == 0) {
    return LargeNum(topNum) - LargeNum(botNum);
  } else if (isPositive == 0 && rhs.isPositive == 1) {
    return LargeNum(botNum) - LargeNum(topNum);
  }

  // checks if the numbers have the same length if not it
  // will be 0
  if (reverseNum.length() > rhs.reverseNum.length()) {
    for (int i = 0; i < reverseNum.length(); i++) {
      int top = 0;
      if (i >= reverseNum.length()) {
        top = 0;
      } else {
        top = reverseNum[i] - '0';
      }

      int bottom = 0;
      if (i >= rhs.reverseNum.length()) {
        bottom = 0;
      } else {
        bottom = rhs.reverseNum[i] - '0';
      }

      int total = top + bottom + carry;

      // pushes the numbers into a string
      // and checks if there is a carry
      if (total > 9) {
        carry = 1;
        answer.push_back((total - 10) + '0');
      } else {
        answer.push_back(total + '0');
        carry = 0;
      }
    }
  } else {
    for (int i = 0; i < rhs.reverseNum.length(); i++) {
      int top = 0;
      if (i >= reverseNum.length()) {
        top = 0;
      } else {
        top = reverseNum[i] - '0';
      }

      int bottom = 0;
      if (i >= rhs.reverseNum.length()) {
        bottom = 0;
      } else {
        bottom = rhs.reverseNum[i] - '0';
      }

      int total = top + bottom + carry;

      // pushes the numbers into a string
      // and checks if there is a carry
      if (total > 9) {
        carry = 1;
        answer.push_back((total - 10) + '0');
      } else {
        answer.push_back(total + '0');
        carry = 0;
      }
    }
  }

  // checks if the sum har a carry that is after the length
  // of the string for example: 82 + 72 = 154
  if (carry != 0) {
    answer.push_back('1');
  }

  reverse(answer.begin(), answer.end());
  LargeNum ans(answer);

  if (isPositive == 0 && rhs.isPositive == 0) {
    ans.isPositive = false;
  }

  return ans;
}

// print out the difference of 2 LargeNum
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  string answer = "";
  int extra = 0;
  string topNum = reverseNum;
  string botNum = rhs.reverseNum;
  reverse(topNum.begin(), topNum.end());
  reverse(botNum.begin(), botNum.end());
  int topNumInt = stoi(topNum);
  int botNumInt = stoi(botNum);

  if (isPositive == 1 && rhs.isPositive == 0) {
    return LargeNum(topNum) + LargeNum(botNum);
  }

  if (topNumInt < botNumInt) {
    for (int i = 0; i < rhs.reverseNum.length(); i++) {
      int top = 0;
      if (i >= rhs.reverseNum.length()) {
        top = 0;
      } else {
        top = rhs.reverseNum[i] - '0';
      }

      int bottom = 0;
      if (i >= reverseNum.length()) {
        bottom = 0;
      } else {
        bottom = reverseNum[i] - '0';
      }

      int total = top - bottom - extra;

      if (total < 0) {
        extra = 1;
        answer.push_back((10 + total) + '0');
      } else {
        answer.push_back(total + '0');
        extra = 0;
      }
    }
    answer.push_back('-');
  } else {
    for (int i = 0; i < reverseNum.length(); i++) {
      int top = 0;
      if (i >= reverseNum.length()) {
        top = 0;
      } else {
        top = reverseNum[i] - '0';
      }

      int bottom = 0;
      if (i >= rhs.reverseNum.length()) {
        bottom = 0;
      } else {
        bottom = rhs.reverseNum[i] - '0';
      }

      int total = top - bottom - extra;

      if (total < 0) {
        extra = 1;
        answer.push_back((10 + total) + '0');
      } else {
        answer.push_back(total + '0');
        extra = 0;
      }
    }
  }
  // checks if the numbers have the same length if not it
  // will be 0

  reverse(answer.begin(), answer.end());
  LargeNum ans(stoi(answer));

  if (isPositive == 0 && rhs.isPositive == 0) {
    ans.isPositive = false;
  }
  return ans;
}

// checks if both numbers are equal ot each other
bool LargeNum::operator==(const LargeNum &rhs) const {
  // if one string is bigger than the other
  if (reverseNum.length() != rhs.reverseNum.length()) {
    return false;
  }

  // checks if the the numbers are both positive or negatif
  if (isPositive != rhs.isPositive && reverseNum != "0") {
    return false;
  }

  // checks all the elements
  for (int i = 0; i < reverseNum.length(); i++) {
    if (reverseNum[i] != rhs.reverseNum[i]) {
      return false;
    }
  }

  return true;
}

// return true if the numbers are not equal
bool LargeNum::operator!=(const LargeNum &rhs) const {
  // checks the length of both strings
  if (reverseNum.length() != rhs.reverseNum.length()) {
    return true;
  }

  // checks if both numbers are positive or negatif
  if (isPositive != rhs.isPositive) {
    return true;
  }

  // checks the elements of the string
  for (int i = 0; i < reverseNum.length(); i++) {
    if (reverseNum[i] != rhs.reverseNum[i]) {
      return true;
    }
  }
  return false;
}

// return true if the left-hand-side number is greater than the
// right-hand-side number
bool LargeNum::operator<(const LargeNum &rhs) const {
  // if the number is the same
  if (reverseNum == rhs.reverseNum) {
    return false;
  }

  // if one number is negative and the other is positive
  if (isPositive == 1 && rhs.isPositive == 0) {
    return false;
  } else if (isPositive == 0 && rhs.isPositive == 1) {
    return true;
  }

  // if both negative numbers
  if (isPositive == 0 && rhs.isPositive == 0) {
    if (reverseNum.length() < rhs.reverseNum.length()) {
      return false;
    } else if (reverseNum.length() > rhs.reverseNum.length()) {
      return true;
    } else {
      for (int i = reverseNum.length() - 1; i > -1; i--) {
        if (reverseNum[i] - '0' > rhs.reverseNum[i] - '0') {
          return true;
        }
      }
    }
  }

  // checks the length of the string
  if (reverseNum.length() < rhs.reverseNum.length()) {
    return true;
  }

  // checks the elements of the string
  for (int i = reverseNum.length() - 1; i > -1; i--) {
    if (reverseNum[i] - '0' > rhs.reverseNum[i] - '0') {
      return false;
    }
  }
  return true;
}

// return true if the left-hand-side number is less than or equal to the
// right-hand-side number
bool LargeNum::operator>(const LargeNum &rhs) const {
  // if the number is the same
  if (reverseNum == rhs.reverseNum) {
    return false;
  }

  // if one of the numbers is negatif
  if (isPositive == 0 && rhs.isPositive == 1) {
    return false;
  } else if (isPositive == 1 && rhs.isPositive == 0) {
    return true;
  }

  // if both negative numbers
  if (isPositive == 0 && rhs.isPositive == 0) {
    if (reverseNum.length() > rhs.reverseNum.length()) {
      return false;
    } else if (reverseNum.length() < rhs.reverseNum.length()) {
      return true;
    } else {
      for (int i = reverseNum.length() - 1; i > -1; i--) {
        if (reverseNum[i] - '0' < rhs.reverseNum[i] - '0') {
          return true;
        }
      }
    }
  }

  // checks the length of both string
  if (reverseNum.length() > rhs.reverseNum.length()) {
    return true;
  }

  // checks the elements of the string
  for (int i = reverseNum.length() - 1; i > -1; i--) {
    if (reverseNum[i] - '0' < rhs.reverseNum[i] - '0') {
      return false;
    }
  }

  return true;
}

// return true if the left-hand-side number is less than the right-hand-side
// number
bool LargeNum::operator<=(const LargeNum &rhs) const {
  // if the number is the same
  if (reverseNum == rhs.reverseNum) {
    return true;
  }

  // if one number is negative and the other is positive
  if (isPositive > rhs.isPositive) {
    return false;
  } else if (isPositive < rhs.isPositive) {
    return true;
  }

  // if both negative numbers
  if (isPositive == 0) {
    if (reverseNum.length() < rhs.reverseNum.length()) {
      return false;
    } else if (reverseNum.length() > rhs.reverseNum.length()) {
      return true;
    } else {
      for (int i = reverseNum.length() - 1; i > -1; i--) {
        if (reverseNum[i] - '0' > rhs.reverseNum[i] - '0') {
          return true;
        }
      }
    }
  }

  // checks the length of the string
  if (reverseNum.length() > rhs.reverseNum.length()) {
    return false;
  }

  // checks the elements of the string
  for (int i = reverseNum.length() - 1; i > -1; i--) {
    if (reverseNum[i] - '0' > rhs.reverseNum[i] - '0') {
      return false;
    }
  }
  return true;
}

// return true if the left-hand-side number is greater than or equal to the
// right-hand-side number
bool LargeNum::operator>=(const LargeNum &rhs) const {
  // if the number is the same
  if (reverseNum == rhs.reverseNum) {
    return true;
  }

  // if one of the numbers is negatif
  if (isPositive == 0 && rhs.isPositive == 1) {
    return false;
  } else if (isPositive == 1 && rhs.isPositive == 0) {
    return true;
  }

  // if both negative numbers
  if (isPositive == 0 && rhs.isPositive == 0) {
    if (reverseNum.length() > rhs.reverseNum.length()) {
      return false;
    } else if (reverseNum.length() < rhs.reverseNum.length()) {
      return true;
    } else {
      for (int i = reverseNum.length() - 1; i > -1; i--) {
        if (reverseNum[i] - '0' < rhs.reverseNum[i] - '0') {
          return true;
        }
      }
    }
  }

  // checks the length of both string
  if (reverseNum.length() > rhs.reverseNum.length()) {
    return true;
  }

  // checks the elements of the string
  for (int i = reverseNum.length() - 1; i > -1; i--) {
    if (reverseNum[i] - '0' < rhs.reverseNum[i] - '0') {
      return false;
    }
  }

  return true;
}

// checks if the number is 0
bool LargeNum::isZero() const {
  if (reverseNum[0] == '0') {
    return true;
  }
  return false;
}

// negate the number, positive becomes negative, negative becomes positive
// Zero is always positive
LargeNum &LargeNum::negate() {
  if (isPositive == 1) {
    isPositive = false;
  } else {
    isPositive = true;
  }
  return *this;
}

// multiply two numbers
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  // any number times 0 = 0
  if (reverseNum == "0" || rhs.reverseNum == "0") {
    return LargeNum(0);
  }

  string top = reverseNum;
  string bot = rhs.reverseNum;
  reverse(top.begin(), top.end());
  reverse(bot.begin(), bot.end());
  LargeNum tmp(top);
  LargeNum tmp2(bot);
  int count = stoi(bot);

  // add the number x times
  while (count != 1) {
    tmp = tmp + LargeNum(top);
    count--;
  }

  // positive number times nnegatif is always negatif
  if (isPositive == 1 && rhs.isPositive == 0) {
    tmp.isPositive = false;
  } else if (isPositive == 0 && rhs.isPositive == 1) {
    tmp.isPositive = false;
  }
  return tmp;
}

// divide two numbers. rhs is the divisor
// similar to integer division, ignore remainder
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  // 0 dived by any number is 0
  if (reverseNum == "0") {
    return LargeNum(0);
  }

  string top = reverseNum;
  string bot = rhs.reverseNum;
  reverse(top.begin(), top.end());
  reverse(bot.begin(), bot.end());
  LargeNum tmp(top);
  LargeNum tmp2(bot);

  if (tmp < tmp2) {
    return LargeNum(0);
  }

  // subtracts the number until it can't be subtracted anymore
  int counter = 0;
  while (tmp >= tmp2) {
    tmp = tmp - tmp2;
    counter++;
  }

  LargeNum ans(counter);
  if (isPositive == 1 && rhs.isPositive == 0) {
    ans.isPositive = false;
  } else if (isPositive == 0 && rhs.isPositive == 1) {
    ans.isPositive = false;
  }

  return ans;
}

// postfix increment
LargeNum LargeNum::operator++(int) {
  string before = reverseNum;
  reverse(before.begin(), before.end());
  int beforeInteger = stoi(before);
  beforeInteger++;
  string after = to_string(beforeInteger);
  reverse(after.begin(), after.end());
  reverseNum = after;

  LargeNum tmp(before);
  tmp.isPositive = isPositive;
  return tmp;
}

// postfix decrement
LargeNum LargeNum::operator--(int) {
  string before = reverseNum;
  reverse(before.begin(), before.end());
  int beforeInteger = stoi(before);
  beforeInteger--;
  string after = to_string(beforeInteger);
  reverse(after.begin(), after.end());
  reverseNum = after;

  LargeNum tmp(before);
  tmp.isPositive = isPositive;
  return tmp;
}

// prefix decrement
LargeNum &LargeNum::operator--() {
  string before = reverseNum;
  if (before == "0") {
    isPositive = false;
  }

  if (isPositive == 0) {
    before.push_back('-');
  }

  reverse(before.begin(), before.end());
  int beforeInteger = stoi(before);
  beforeInteger--;
  string after = to_string(beforeInteger);
  reverse(after.begin(), after.end());
  if (isPositive == 0) {
    after.pop_back();
  }
  reverseNum = after;

  return *this;
}

// prefix increment
LargeNum &LargeNum::operator++() {
  string before = reverseNum;
  if (isPositive == 0) {
    before.push_back('-');
  }

  reverse(before.begin(), before.end());
  int beforeInteger = stoi(before);
  beforeInteger++;
  if (beforeInteger >= 0) {
    isPositive = true;
  }
  string after = to_string(beforeInteger); // 0
  reverse(after.begin(), after.end());

  if (isPositive == 0) {
    after.pop_back();
  }
  reverseNum = after;

  return *this;
}