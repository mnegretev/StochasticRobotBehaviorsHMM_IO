
"use strict";

let InputsSrv = require('./InputsSrv.js')
let SensorSrv = require('./SensorSrv.js')
let InputsPlannerSrv = require('./InputsPlannerSrv.js')
let ReadySrv = require('./ReadySrv.js')
let MVServ = require('./MVServ.js')
let LightRealSrv = require('./LightRealSrv.js')
let LightSrv = require('./LightSrv.js')
let GetLaserServ = require('./GetLaserServ.js')
let OverSrv = require('./OverSrv.js')

module.exports = {
  InputsSrv: InputsSrv,
  SensorSrv: SensorSrv,
  InputsPlannerSrv: InputsPlannerSrv,
  ReadySrv: ReadySrv,
  MVServ: MVServ,
  LightRealSrv: LightRealSrv,
  LightSrv: LightSrv,
  GetLaserServ: GetLaserServ,
  OverSrv: OverSrv,
};
