//This file is automatically generated. DO NOT EDIT!

#include <RobotRaconteur.h>
#include <boost/signals2.hpp>
#pragma once

namespace example
{
namespace math
{

class MathSolver;

class MathSolver : public virtual RobotRaconteur::RRObject
{
public:
virtual int32_t get_value()=0;
virtual void set_value(int32_t value)=0;

virtual double add(double a, double b)=0;

virtual double dot(RR_SHARED_PTR<RobotRaconteur::RRArray<double > > a, RR_SHARED_PTR<RobotRaconteur::RRArray<double > > b)=0;

virtual RR_SHARED_PTR<RobotRaconteur::RRArray<double > > sort_sequence(RR_SHARED_PTR<RobotRaconteur::RRArray<double > > seq, std::string dir)=0;

virtual std::string RRType() {return "example.math.MathSolver";  }
};

}
}

