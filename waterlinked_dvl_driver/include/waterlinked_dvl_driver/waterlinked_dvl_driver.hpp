// Copyright 2024, Evan Palmer
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <memory>

#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
#include "libwaterlinked/client.hpp"
#include "marine_acoustic_msgs/msg/dvl.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"
#include "std_srvs/srv/set_bool.hpp"
#include "std_srvs/srv/trigger.hpp"

// auto-generated by generate_parameter_library
#include "waterlinked_dvl_driver_parameters.hpp"

namespace waterlinked::ros
{

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class WaterLinkedDvlDriver : public rclcpp_lifecycle::LifecycleNode
{
public:
  explicit WaterLinkedDvlDriver(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

  auto on_configure(const rclcpp_lifecycle::State & previous_state) -> CallbackReturn override;

  auto on_activate(const rclcpp_lifecycle::State & previous_state) -> CallbackReturn override;

private:
  std::unique_ptr<WaterLinkedClient> client_;

  std::shared_ptr<waterlinked_dvl_driver::ParamListener> param_listener_;
  waterlinked_dvl_driver::Params params_;

  // Declare the DVL and dead reckoning messages to avoid re-initializing them every time they are published
  marine_acoustic_msgs::msg::Dvl dvl_msg_;
  geometry_msgs::msg::PoseWithCovarianceStamped dead_reckoning_msg_;
  nav_msgs::msg::Odometry odom_msg_;

  std::shared_ptr<rclcpp::Publisher<marine_acoustic_msgs::msg::Dvl>> dvl_pub_;
  std::shared_ptr<rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>> dead_reckoning_pub_;
  std::shared_ptr<rclcpp::Publisher<nav_msgs::msg::Odometry>> odom_pub_;

  std::shared_ptr<rclcpp::Service<std_srvs::srv::SetBool>> enable_acoustic_srv_;
  std::shared_ptr<rclcpp::Service<std_srvs::srv::SetBool>> enable_dark_mode_srv_;
  std::shared_ptr<rclcpp::Service<std_srvs::srv::SetBool>> enable_periodic_cycling_srv_;

  std::shared_ptr<rclcpp::Service<std_srvs::srv::Trigger>> calibrate_gyro_srv_;
  std::shared_ptr<rclcpp::Service<std_srvs::srv::Trigger>> reset_dead_reckoning_srv_;
  std::shared_ptr<rclcpp::Service<std_srvs::srv::Trigger>> trigger_ping_srv_;
};

}  // namespace waterlinked::ros

RCLCPP_COMPONENTS_REGISTER_NODE(waterlinked::ros::WaterLinkedDvlDriver)
