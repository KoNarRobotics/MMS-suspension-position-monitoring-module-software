#pragma once
#include "encoder_magnetic.hpp"
#include "i2c.hpp"
#include "main.hpp"
#include "main_prog.hpp"
#include "status.hpp"
#include "stmepic.hpp"
#include "uart.hpp"

#include "MT6701.hpp"
#include "uart.hpp"

#include "can_mc_driver.hpp"
#include "mc_firmware/can_base.hpp"
#include "mc_firmware/mc_common.hpp"

uint32_t get_unique_id() {
  uint32_t t1 = HAL_GetUIDw0();
  uint32_t t2 = HAL_GetUIDw1();
  uint32_t t3 = HAL_GetUIDw2();
  return (t1 ^ t2 ^ t3) & 0x1FFFFF; // Return only the lower 21 bits
}

se::SimpleTask task_module_control_loop;

///////////////////////////////////////////////////////////////////////////////
/// PLACE FOR YOUR CUSTOM MODULES INITIALIZATION AND DEFINITIONS

// class CanTranslatorMcSe : public mcan::CanBase {
// public:
//   CanTranslatorMcSe(std::shared_ptr<se::CanBase> can_interface)
//       : _can_interface(std::move(can_interface)) {}

//   Status write(const mcan::CanFrame &msg) override {
//     se::CanDataFrame data_frame;
//     data_frame.id = msg.id;
//     data_frame.size = msg.size;
//     data_frame.remote_request = msg.is_remote_request;
//     data_frame.extended_id = msg.is_extended;
//     data_frame.fdcan_frame = false; // Assuming CAN 2.0 frame, change if
//     needed std::memcpy(data_frame.data, msg.data, msg.size); return
//     _can_interface->write(data_frame);
//   }

//   Status add_callback(uint32_t frame_id, can_callback_type callback,
//                      void *args = nullptr) override {
//     auto wrapper_callback = [callback](se::CanBase &cb, const
//     se::CanDataFrame &data_frame, void *args) {
//       mcan::CanFrame msg;
//       msg.id = data_frame.id;
//       msg.size = data_frame.data_size;
//       msg.remote_request = data_frame.remote_request;
//       msg.extended_id = data_frame.extended_id;
//       msg.fdcan_frame = data_frame.fdcan_frame;
//       std::memcpy(msg.data, data_frame.data, data_frame.data_size);
//       callback(cb, msg, args);
//     };
//     return _can_interface->add_callback(frame_id, wrapper_callback, args);
//   }

// private:
//   std::shared_ptr<se::CanBase> _can_interface;
// };

#include "motor_hat.hpp"

using ModuleType = mcan::McSlaveDriver<mcan::motor_hat::McCanSlaveInterface_t,
                                       mcan::motor_hat::Hardware_t>;

extern std::shared_ptr<ModuleType> module;