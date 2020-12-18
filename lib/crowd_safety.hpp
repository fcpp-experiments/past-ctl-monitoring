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

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

  namespace tags {
    //! @brief Parametric tag for formula failure.
    template <typename T>
    struct fail {};
    //! @brief Local value of the strong monitor formula.
    struct local_strong_monitor {};
    //! @brief Local value of the weak monitor formula.
    struct local_weak_monitor {};
    //! @brief Global value of the strong monitor formula.
    struct global_strong_monitor {};
    //! @brief Global value of the weak monitor formula.
    struct global_weak_monitor {};
    //! @brief Color representing the distance of the current node.
    struct distance_c {};
    //! @brief Size of the current node.
    struct size {};
  }

  //! @brief number of areas (one of which is the incident area)
  constexpr int nareas = 12;  

  //! @brief ID of the incident area
  constexpr int idinc = 6;

  //! @brief start time of the incident
  constexpr int inc_start = 20;

  //! @brief end time of the incident  
  constexpr int inc_end = 50;  

  //! @brief radius of the incident effects
  constexpr double inc_radius = 30;
  
  //! @brief Main function.
  MAIN() {
    bool isinc = (node.uid == idinc);
    bool isarea = (node.uid < nareas);
  
    vec<2> low = make_vec(0,0);
    vec<2> high = make_vec(500,500);
    
    if (!isarea)
      rectangle_walk(CALL, low, high, 30.5, 1); 

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
    
    double dist = abf_distance(CALL, isinc);
    if (dist<inc_radius) {
      safe = false;
    }

    bool my_safety_preserved = logic::my_safety_preserved(CALL, safe, alert);
    bool all_safety_preserved = logic::all_safety_preserved(CALL, safe, alert);
    
    if (isarea) {
      node.storage(tags::distance_c{}) = BLUE;      
      if (isinc) {
	if (alert)
	  node.storage(tags::distance_c{}) = YELLOW;
	else
	  node.storage(tags::distance_c{}) = BLUE;      
      }
    } else if (safe)
      node.storage(tags::distance_c{}) = GREEN;
    else
      node.storage(tags::distance_c{}) = RED;
 }

}
}

#endif // FCPP_CROWD_SAFETY_H_
