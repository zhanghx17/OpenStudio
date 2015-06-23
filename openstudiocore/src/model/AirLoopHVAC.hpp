/**********************************************************************
 *  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef MODEL_AIRLOOPHVAC_HPP
#define MODEL_AIRLOOPHVAC_HPP

#include "ModelAPI.hpp"
#include "Loop.hpp"

namespace openstudio {

namespace model {

namespace detail {
  class AirLoopHVAC_Impl;
};

class Node;
class AirLoopHVACOutdoorAirSystem;
class AirLoopHVACZoneSplitter;
class AirLoopHVACZoneMixer;
class AirLoopHVACSupplyPlenum;
class AirLoopHVACReturnPlenum;
class StraightComponent;
class ThermalZone;
class SizingSystem;

/** AirLoopHVAC is an interface to the EnergyPlus IDD object named "AirLoopHVAC"
 *
 * The purpose of this class is to simplify the construction and manipulation
 * air loops in energyplus.  Presently, only single zone air loops with one
 * supply branch are supported, however more complicated air loop topologies
 * are planned, including all of those supported by EnergyPlus.
 */
class MODEL_API AirLoopHVAC : public Loop
{
  public:

  /** Constructs a new AirLoopHVAC object and places it inside the
   * model.  The air loop is fully initialized with the companion objects
   * that are needed for a basic air loop in EnergyPlus.  These objects include:
   * supply inlet node, supply outlet node, demand inlet node, demand outlet node,
   * zone splitter, zone mixer, and zone hvac equipment connections.
   */
  explicit AirLoopHVAC(Model& model);

  virtual ~AirLoopHVAC() {}


  boost::optional<double> designSupplyAirFlowRate() const;

  OSOptionalQuantity getDesignSupplyAirFlowRate(bool returnIP=false) const;

  bool isDesignSupplyAirFlowRateAutosized() const;

  void setDesignSupplyAirFlowRate(double designSupplyAirFlowRate);

  bool setDesignSupplyAirFlowRate(const Quantity& designSupplyAirFlowRate);

  void resetDesignSupplyAirFlowRate();

  void autosizeDesignSupplyAirFlowRate();


  /** Returns the supply inlet node. */
  Node supplyInletNode() const override;

  /** Returns the supply outlet nodes.
   * Single duct systems have one supply outlet node.
   * Dual duct systems have two supply outlet nodes.
   */
  std::vector<Node> supplyOutletNodes() const override;

  /** Returns the first supply outlet Node. */
  Node supplyOutletNode() const override;

  /** Returns the demand inlet nodes.
   * Single duct systems have one demand inlet node.
   * Dual duct systems have two demand inlet nodes.
   */
  std::vector<Node> demandInletNodes() const override;

  /** Returns the first demand inlet Node. */
  Node demandInletNode() const override;

  /** Returns the demand outlet node */
  Node demandOutletNode() const override;

  /** Returns the outdoor air node.  This is the outermost node from which
   * outdoor air is introduced into the air loop.  This node only exists if there
   * is an outdoor air system within the air loop.  A freshly constructed
   * AirLoopHVAC object will not have an outdoor air system.
   */
  boost::optional<Node> outdoorAirNode();

  /** Returns the relief air node.  This is the outermost node from which
   * air is relieved from the air loop to the outdoor air.  This node only exists
   * if there is an outdoor air system within the air loop.  A freshly
   * constructed AirLoopHVAC object will not have an outdoor air system.
   */
  boost::optional<Node> reliefAirNode();

  /** Returns the mixed air node.  This is the mixed air node of the outdoor
   * air mixer of the air loop.  This node only exists if there is an outdoor air
   * system within the air loop.  A freshly constructed AirLoopHVAC object
   * will not have an outdoor air system.
   */
  boost::optional<Node> mixedAirNode();

  /** Returns the return air node.  This is the return air node of the outdoor
   * air mixer of the air loop.  This node only exists if there is an outdoor air
   * system within the air loop.  A freshly constructed AirLoopHVAC object
   * will not have an outdoor air system.  In many cases this node will be the
   * same as the supply inlet node, because there is often no hvac equipment
   * before the outdoor air mixer.
   */
  boost::optional<Node> returnAirNode();

  /** Returns the supply side splitter.  If the system is a dual duct
   * or has a return air bypass then it will have a supply side splitter.
   */
  boost::optional<Splitter> supplySplitter() const;

  /** Returns the supply side splitter inlet node.  If the system is a dual duct
   * or has a return air bypass then it will have a supply side splitter.
   */
  boost::optional<Node> supplySplitterInletNode() const;

  /** Returns the supply side splitter outlet nodes.  If the system is a dual duct
   * or has a return air bypass then it will have a supply side splitter.
   */
  std::vector<Node> supplySplitterOutletNodes() const;

  /** Returns the first zone splitter.
   */
  AirLoopHVACZoneSplitter zoneSplitter() const;

  /** Returns the zone splitters.
   * Single duct systems have one zone splitter, dual duct systems have two.
   */
  std::vector<AirLoopHVACZoneSplitter> zoneSplitters() const;

  /** Returns the zone mixer, if it doesn't exist then it makes one. */
  AirLoopHVACZoneMixer zoneMixer();

  /** Returns all of the components on the outdoor air system including the mixer itself.
   *  If type is given then the results will be limited to the given IddObjectType.
   */
  std::vector<ModelObject> oaComponents(openstudio::IddObjectType type = openstudio::IddObjectType("Catchall"));

  /** Returns the AirLoopHVACOutdoorAirSystem object associated with the air loop.
   * A freshly constructed AirLoopHVAC object will not have an outdoor air system
   * and this method will return a false optional.
   */
  boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

  /** Returns the fan in the mixed air stream (after outdoor air system) of the air system.
   *  If there is no outdoor air system or there are multiple fans in the mixed air stream, 
   *  then the fan closest to the supply outlet node will be returned.
   */
  boost::optional<HVACComponent> supplyFan() const;

  /** Returns the fan in the return air stream (before the outdoor air system.
   *  If there is no outdoor air system then this method will return false.
   *  If there are multiple fans, then return the fan nearest the oa system.
   */
  boost::optional<HVACComponent> returnFan() const;

  /** Returns the most outboard fan on the relief air stream of the outdoor air system */
  boost::optional<HVACComponent> reliefFan() const;

  /** Adds a new branch on the demand side of the air loop for a zone labeled zoneLabel
   * and returns true if the operation was successful. The method will return false if the Zone
   * is already connected to an air loop.
   * New code should favor addBranchForZone(ThermalZone &) or addBranchForZone(ThermalZone &, HVACComponent&).
   */
  bool addBranchForZone(openstudio::model::ThermalZone & thermalZone,
                        boost::optional<StraightComponent> optAirTerminal);

  /** Overloaded version of addBranchForZone() **/
  bool addBranchForZone(openstudio::model::ThermalZone & thermalZone);

  /** Overloaded version of addBranchForZone() **/
  bool addBranchForZone(ThermalZone & thermalZone, HVACComponent & airTerminal);

  /** Adds a new branch on the demand side of the air loop with the specified airTerminal.
   *  Returns true if the airTerminal was accepted, otherwise false.  The argument, hvacComponent,
   *  can be an air terminal, AirLoopHVACSupplyPlenum, or airLoopHVACReturnPlenum.
   **/
  bool addBranchForHVACComponent(HVACComponent hvacComponent);

  /** Removes the Zone identified by zoneLabel from the air loop and returns true
   * upon successful removal.
   **/
  bool removeBranchForZone(openstudio::model::ThermalZone & thermalZone);

  /** Returns the Sizing:System object associated with this air loop. **/
  SizingSystem sizingSystem() const;

  /** Returns the ThermalZone objects attached to this air loop. **/
  std::vector<ThermalZone> thermalZones() const;

  /** Returns the availability schedule when this system is allowed to run. **/
  Schedule availabilitySchedule() const;

  /** Set the availability schedule for when this system is allowed to run. **/
  void setAvailabilitySchedule(Schedule & schedule);

  /** Configure the system to night cycle
   *  Valid options are StayOff, CycleOnAny, and CycleOnAnyZoneFansOnly **/
  bool setNightCycleControlType(std::string controlType);

  /** Returns a string indicating if the system is configured to night cycle **/
  std::string nightCycleControlType() const;

  std::vector<openstudio::IdfObject> remove() override;

  ModelObject clone(Model model) const override;

  static IddObjectType iddObjectType();

 protected:

  friend class Model;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  /// @cond

  typedef detail::AirLoopHVAC_Impl ImplType;

  explicit AirLoopHVAC(std::shared_ptr<ImplType> impl);

  private:

  REGISTER_LOGGER("openstudio.model.AirLoopHVAC");

  /// @endcond

};

// optional AirLoopHVAC
typedef boost::optional<AirLoopHVAC> OptionalAirLoopHVAC;

// vector of AirLoopHVAC
typedef std::vector<AirLoopHVAC> AirLoopHVACVector;

} // model

} // openstudio

#endif // MODEL_AIRLOOPHVAC_HPP
