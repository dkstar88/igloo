
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTRESULTS_H
#define IGLOO_TESTRESULTS_H

namespace igloo {

  class TestResults 
  {
    public:

      int NumberOfTestsRun() const
      {
        return testResults_.size();
      }

      int NumberOfSucceededTests() const
      {
        return std::count_if(begin(), end(), SpecSucceeded);
      }

      int NumberOfFailedTests() const
      {
        return NumberOfTestsRun() - NumberOfSucceededTests();
      }

      void AddResult(const TestResult result)
      {
        testResults_.push_back(result);

        if(result.GetSuccess())
        {
          succeededTests_.push_back(result);
        }
        else
        {
          failedTests_.push_back(result);
        }
      }

      typedef std::list<TestResult>::const_iterator const_iterator;
      typedef std::list<TestResult>::size_type size_type;

      const_iterator begin() const
      {
        return testResults_.begin();
      }

      const_iterator end() const
      {
        return testResults_.end();
      }

      size_type size() const
      {
        return testResults_.size();
      }

      const std::list<TestResult>& FailedTests() const
      {
        return failedTests_;
      }

      const std::list<TestResult>& SucceededTests() const
      {
        return succeededTests_;
      }

      friend std::ostream& operator<<(std::ostream& stm, const TestResults& results);

    private:
      std::list<TestResult> testResults_;
      std::list<TestResult> failedTests_;
      std::list<TestResult> succeededTests_;

      static bool SpecSucceeded(const TestResult& spec)
      {
        return spec.GetSuccess();
      }
  };


  inline std::ostream& operator<<(std::ostream& stm, const TestResults& results)
  {
    stm << "[ ";
    TestResults::const_iterator it;
    for(it = results.begin(); it != results.end(); it++)
    {
      stm << "< " << *it << " >";
    }

    stm << " ]";

    return stm;
  }
}

#endif
