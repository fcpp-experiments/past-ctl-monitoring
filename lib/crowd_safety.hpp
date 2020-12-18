// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file crowd_safety.hpp
 * @brief Implementation of the case study on crowd safety.
 */

#ifndef FCPP_CROWD_SAFETY_H_
#define FCPP_CROWD_SAFETY_H_

#include "lib/data.hpp"
#include "lib/logic_samples.hpp"
#include "lib/past_ctl.hpp"
#include "lib/data/vec.hpp"
#include "lib/coordination/time.hpp"

/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

  bool operator< (const vec<2>& v1, const vec<2>& v2) {
    return false;
  }

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

  namespace tags {
    //! @brief Parametric tag for formula failure.
    template <typename T>
    struct fail {};
    //! @brief Local value of the monitor formula.
    struct local_safety_monitor {};
    //! @brief Global value of the monitor formula.
    struct global_safety_monitor {};
    //! @brief Color representing the distance of the current node.
    struct col {};
    //! @brief Size of the current node.
    struct size {};
  }

  
  //! @brief number of areas (one of which is the incident area)
  constexpr int nareas = 12;  

  //! @brief ID of the incident area
  constexpr int idinc = 8;

  //! @brief start time of the incident
  constexpr int inc_start = 10;

  //! @brief end time of the incident  
  constexpr int inc_end = 30;  

  //! @brief radius of the incident effects
  constexpr double inc_radius = 30;

  //! @brief radius of the incident effects
  constexpr double max_speed = 30;

  //! @brief radius of the incident effects
  constexpr double period = 1;
  
  //! @brief Main function.
  MAIN() {
    using namespace tags;
    
    bool isinc = (node.uid == idinc);
    bool isarea = (node.uid < nareas);
  
    vec<2> low = make_vec(0,0);
    vec<2> high = make_vec(500,500);

    //bool r = myf(low,high);
    
    // vec<2> pos = node.position();
    // vec<2> target = random_rectangle_target(CALL, low, high);
    
    // double dist = norm(pos-target);
    
    node.storage(tags::size{}) = isarea ? 10 : 5;
    if (isinc)
      node.storage(tags::size{}) = 15;
    
    bool safe = true;
    bool alert = false;
    
    double t = node.current_time();
    // if (isinc) {
    //   if (t>50 && t<100)
    // 	alert = true;
    // }

    // for now, everyone knows (hears) about alarms
    if (t>=inc_start && t<=inc_end)
      alert = true;    
    
    double dist = bis_distance(CALL, isinc, period, max_speed);
    if (dist<inc_radius) {
      safe = false;
    }
    bool getaway = (dist < inc_radius*1.5);

    if (!isarea)
      if(alert && getaway) {
	// //OK
	// auto f = make_tuple(nbr(CALL, dist), nbr(CALL, make_tuple(1.0,2.0)));
	// auto target = get<1>(max_hood(CALL, f));      
	//KO
	auto f = make_tuple(nbr(CALL, dist), node.nbr_vec());
	auto target = get<1>(max_hood(CALL, f));
      
	follow_target(CALL, target, max_speed, period);			     
      } else
	rectangle_walk(CALL, low, high, max_speed, period);
    
    bool my_safety_preserved = logic::my_safety_preserved(CALL, safe, alert);
    bool all_safety_preserved = logic::all_safety_preserved(CALL, safe, alert);

    node.storage(fail<local_safety_monitor>{}) = not my_safety_preserved;
    node.storage(fail<global_safety_monitor>{}) = not all_safety_preserved;

    if (isarea) {
      node.storage(col{}) = BLUE;      
      if (isinc && alert)
	  node.storage(col{}) = YELLOW;
    } else if (safe)
      node.storage(col{}) = GREEN;
    else
      node.storage(col{}) = RED;
 }

}
}

#endif // FCPP_CROWD_SAFETY_H_
