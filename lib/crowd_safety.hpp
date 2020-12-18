// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file crowd_safety.hpp
 * @brief Implementation of the case study on crowd safety.
 */

#ifndef FCPP_CROWD_SAFETY_H_
#define FCPP_CROWD_SAFETY_H_

#include "lib/data.hpp"
#include "lib/logic_samples.hpp"
#include "lib/data/vec.hpp"
#include "lib/coordination/time.hpp"

/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

      namespace tags {
      //! @brief Distance of the current node.
      struct my_distance {};
      //! @brief Diameter of the network (in the source).
      struct source_diameter {};
      //! @brief Diameter of the network (in every node).
      struct diameter {};
      //! @brief Color representing the distance of the current node.
      struct distance_c {};
      //! @brief Color representing the diameter of the network (in the source).
      struct source_diameter_c {};
      //! @brief Color representing the diameter of the network (in every node).
      struct diameter_c {};
      //! @brief Size of the current node.
      struct size {};
    }

  

  //! @brief Main function.
  MAIN() {
    constexpr int nareas = 12;
    constexpr int idinc = 6;
    constexpr int inc_start = 20;
    constexpr int inc_end = 50;
    constexpr double inc_radius = 30;
    
    // device_t source_id = 50;
    // bool is_source = node.uid == source_id;

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

    // for now, everyonme knows about alarms
    if (t>=inc_start && t<=inc_end)
      alert = true;    
    
    double dist = abf_distance(CALL, isinc);
    if (dist<inc_radius) {
      safe = false;
    }
    
    double sdiam = mp_collection(CALL, dist, dist, 0.0, [](double x, double y){
							  return max(x, y);
							}, [](double x, int){
							     return x;
							   });
    double diam = broadcast(CALL, dist, sdiam);

    node.storage(tags::my_distance{}) = dist;
    node.storage(tags::source_diameter{}) = sdiam;
    node.storage(tags::diameter{}) = diam;
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
    //color::hsva(10, 1, 1);
    else
      node.storage(tags::distance_c{}) = RED;
    //color::hsva(20, 1, 1);
    
    node.storage(tags::source_diameter_c{}) = color::hsva(sdiam, 1, 1);
    node.storage(tags::diameter_c{}) = color::hsva(diam, 1, 1);
 }

}


  
// //! @brief Namespace containing the libraries of coordination routines.
// namespace coordination {

// //! @brief Crowd safety case study.
// MAIN() {
//     bool safe = true;
//     bool alert = false;
//     bool my_safety_preserved = logic::my_safety_preserved(CALL, safe, alert);
//     bool all_safety_preserved = logic::all_safety_preserved(CALL, safe, alert);
//     // TODO: people randomly walking in area; then a sub-area becomes dangerous and they evacuate through gradients
// }

// }


}

#endif // FCPP_CROWD_SAFETY_H_
