//
//  BroodWar.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-03.
//
//

#pragma once

namespace StarCraft {
	namespace Player {
		enum : u8 {
			P1,
			P2,
			P3,
			P4,
			P5,
			P6,
			P7,
			P8,
			P9,
			P10,
			P11,
			P12,
			
			COUNT,
			COUNT_PLAYABLE = P9,
			
			Neutral = P12
		};
	}

	namespace Unit {
		enum : u8 {
			TerranMarine,
			TerranGhost,
			TerranVulture,
			TerranGoliath,
			GoliathTurret,
			TerranSiegeTank_TankMode,
			SiegeTankTurret_TankMode,
			TerranSCV,
			TerranWraith,
			TerranScienceVessel,
			GuiMontag_Firebat,
			TerranDropship,
			TerranBattlecruiser,
			SpiderMine,
			NuclearMissile,
			TerranCivilian,
			SarahKerrigan_Ghost,
			AlanSchezar_Goliath,
			AlanSchezarTurret,
			JimRaynor_Vulture,
			JimRaynor_Marine,
			TomKazansky_Wraith,
			Magellan_ScienceVessel,
			EdmundDuke_TankMode,
			EdmundDukeTurret_TankMode,
			EdmundDuke_SiegeMode,
			EdmundDukeTurret_SiegeMode,
			ArcturusMengsk_Battlecruiser,
			Hyperion_Battlecruiser,
			NoradII_Battlecruiser,
			TerranSiegeTank_SiegeMode,
			SiegeTankTurret_SiegeMode,
			TerranFirebat,
			ScannerSweep,
			TerranMedic,
			ZergLarva,
			ZergEgg,
			ZergZergling,
			ZergHydralisk,
			ZergUltralisk,
			ZergBroodling,
			ZergDrone,
			ZergOverlord,
			ZergMutalisk,
			ZergGuardian,
			ZergQueen,
			ZergDefiler,
			ZergScourge,
			Torrasque_Ultralisk,
			Matriarch_Queen,
			InfestedTerran,
			InfestedKerrigan_InfestedTerran,
			UncleanOne_Defiler,
			HunterKiller_Hydralisk,
			DevouringOne_Zergling,
			Kukulza_Mutalisk,
			Kukulza_Guardian,
			Yggdrasill_Overlord,
			TerranValkyrie,
			MutaliskCocoon,
			ProtossCorsair,
			ProtossDarkTemplar_Unit,
			ZergDevourer,
			ProtossDarkArchon,
			ProtossProbe,
			ProtossZealot,
			ProtossDragoon,
			ProtossHighTemplar,
			ProtossArchon,
			ProtossShuttle,
			ProtossScout,
			ProtossArbiter,
			ProtossCarrier,
			ProtossInterceptor,
			ProtossDarkTemplar_Hero,
			Zeratul_DarkTemplar,
			ProtossArchon_Hero,
			Fenix_Zealot,
			Fenix_Dragoon,
			Tassadar_Templar,
			Mojo_Scout,
			Warbringer_Reaver,
			Gantrithor_Carrier,
			ProtossReaver,
			ProtossObserver,
			ProtossScarab,
			Danimoth_Arbiter,
			Aldaris_Templar,
			Artanis_Scout,
			Rhynadon_BadlandsCritter,
			Bengalaas_JungleCritter,
			CargoShip_Unused,
			MercenaryGunship_Unused,
			Scantid_DesertCritter,
			Kakaru_TwilightCritter,
			Ragnasaur_AshworldCritter,
			Ursadon_IceWorldCritter,
			LurkerEgg,
			Raszagal_Corsair,
			SamirDuran_Ghost,
			AlexeiStukov_Ghost,
			MapRevealer,
			GerardDuGalle_BattleCruiser,
			ZergLurker,
			InfestedDuran_InfestedTerran,
			DisruptionWeb,
			TerranCommandCenter,
			TerranComsatStation,
			TerranNuclearSilo,
			TerranSupplyDepot,
			TerranRefinery,
			TerranBarracks,
			TerranAcademy,
			TerranFactory,
			TerranStarport,
			TerranControlTower,
			TerranScienceFacility,
			TerranCovertOps,
			TerranPhysicsLab,
			Starbase_Unused,
			TerranMachineShop,
			RepairBay_Unused,
			TerranEngineeringBay,
			TerranArmory,
			TerranMissileTurret,
			TerranBunker,
			NoradII_Crashed,
			IonCannon,
			UrajCrystal,
			KhalisCrystal,
			InfestedCommandCenter,
			ZergHatchery,
			ZergLair,
			ZergHive,
			ZergNydusCanal,
			ZergHydraliskDen,
			ZergDefilerMound,
			ZergGreaterSpire,
			ZergQueensNest,
			ZergEvolutionChamber,
			ZergUltraliskCavern,
			ZergSpire,
			ZergSpawningPool,
			ZergCreepColony,
			ZergSporeColony,
			UnusedZergBuilding1,
			ZergSunkenColony,
			ZergOvermind_WithShell,
			ZergOvermind,
			ZergExtractor,
			MatureChrysalis,
			ZergCerebrate,
			ZergCerebrateDaggoth,
			UnusedZergBuilding2,
			ProtossNexus,
			ProtossRoboticsFacility,
			ProtossPylon,
			ProtossAssimilator,
			UnusedProtossBuilding1,
			ProtossObservatory,
			ProtossGateway,
			UnusedProtossBuilding2,
			ProtossPhotonCannon,
			ProtossCitadelofAdun,
			ProtossCyberneticsCore,
			ProtossTemplarArchives,
			ProtossForge,
			ProtossStargate,
			StasisCell,
			ProtossFleetBeacon,
			ProtossArbiterTribunal,
			ProtossRoboticsSupportBay,
			ProtossShieldBattery,
			KhaydarinCrystalFormation,
			ProtossTemple,
			XelNagaTemple,
			MineralField_Type1,
			MineralField_Type2,
			MineralField_Type3,
			Cave_Unused,
			CaveIn_Unused,
			Cantina_Unused,
			MiningPlatform_Unused,
			IndependentCommandCenter_Unused,
			IndependentStarport_Unused,
			IndependentJumpGate_Unused,
			Ruins_Unused,
			KhaydarinCrystalFormation_Unused,
			VespeneGeyser,
			WarpGate,
			PsiDisrupter,
			ZergMarker,
			TerranMarker,
			ProtossMarker,
			ZergBeacon,
			TerranBeacon,
			ProtossBeacon,
			ZergFlagBeacon,
			TerranFlagBeacon,
			ProtossFlagBeacon,
			PowerGenerator,
			OvermindCocoon,
			DarkSwarm,
			FloorMissileTrap,
			FloorHatch_Unused,
			LeftUpperLevelDoor,
			RightUpperLevelDoor,
			LeftPitDoor,
			RightPitDoor,
			FloorGunTrap,
			LeftWallMissileTrap,
			LeftWallFlameTrap,
			RightWallMissileTrap,
			RightWallFlameTrap,
			StartLocation,
			Flag,
			YoungChrysalis,
			PsiEmitter,
			DataDisc,
			KhaydarinCrystal,
			MineralClusterType1,
			MineralClusterType2,
			ProtossVespeneGasOrbType1,
			ProtossVespeneGasOrbType2,
			ZergVespeneGasSacType1,
			ZergVespeneGasSacType2,
			TerranVespeneGasTankType1,
			TerranVespeneGasTankType2,
			
			COUNT,
			
			Tassadar_Archon = ProtossArchon_Hero,
			Zeratul_Archon = ProtossArchon_Hero
		};
	}
	
	namespace Technology {
		enum : u8 {
			StimPacks,
			Lockdown,
			EMPShockwave,
			SpiderMines,
			ScannerSweep,
			SiegeMode,
			DefensiveMatrix,
			Irradiate,
			YamatoGun,
			CloakingField,
			PersonnelCloaking,
			Burrowing,
			Infestation,
			SpawnBroodling,
			DarkSwarm,
			Plague,
			Consume,
			Ensnare,
			Parasite,
			PsionicStorm,
			Hallucination,
			Recall,
			
			COUNT
		};
	}
	
	namespace Upgrade {
		enum : u8 {
			TerranInfantryArmor,
			TerranVehiclePlating,
			TerranShipPlating,
			ZergCarapace,
			ZergFlyerCaparace,
			ProtossArmor,
			ProtossPlating,
			TerranInfantryWeapons,
			TerranVehicleWeapons,
			TerranShipWeapons,
			ZergMeleeAttacks,
			ZergMissileAttacks,
			ZergFlyerAttacks,
			ProtossGroundWeapons,
			ProtossAirWeapons,
			ProtossPlasmaShields,
			U238Shells,
			IonThrusters,
			BurstLasers_Unused,
			TitanReactor,
			OcularImplants,
			MoebiusReactor,
			ApolloReactor,
			ColossusReactor,
			VentralSacs,
			Antennae,
			PneumatizedCarapace,
			MetabolicBoost,
			AdrenalGlands,
			MuscularAugments,
			GroovedSpines,
			GameteMeiosis,
			MetasynapticNode,
			SingularityCharge,
			LegEnhancements,
			ScarabDamage,
			ReaverCapacity,
			GraviticDrive,
			SensorArray,
			GraviticBoosters,
			KhaydarinAmulet,
			ApialSensors,
			GraviticThrusters,
			CarrierCapacity,
			KhaydarinCore,
			Unknown45,
			
			COUNT
		};
	}
	
	namespace Weapon {
		enum : u8 {
			GaussRifle_Normal,
			GaussRifle_JimRaynor,
			C10ConcussionRifle_Normal,
			C10ConcussionRifle_SarahKerrigan,
			FragmentationGrenade_Normal,
			FragmentationGrenade_JimRaynor,
			SpiderMines,
			TwinAutocannons_Normal,
			HellfireMissilePack_Normal,
			TwinAutocannons_AlanSchezar,
			HellfireMissilePack_AlanSchezar,
			ArcliteCannon_Normal,
			ArcliteCannon_EdmundDuke,
			FusionCutter,
			FusionCutter_Harvest,
			GeminiMissiles_Normal,
			BurstLasers_Normal,
			GeminiMissiles_TomKazansky,
			BurstLasers_TomKazansky,
			ATSLaserBattery_Normal,
			ATALaserBattery_Normal,
			ATSLaserBattery_Hero,
			ATALaserBattery_Hero,
			ATSLaserBattery_Hyperion,
			ATALaserBattery_Hyperion,
			FlameThrower_Normal,
			FlameThrower_GuiMontag,
			ArcliteShockCannon_Normal,
			ArcliteShockCannon_EdmundDuke,
			LongboltMissiles,
			YamatoGun,
			NuclearMissile,
			Lockdown,
			EMPShockwave,
			Irradiate,
			Claws_Normal,
			Claws_DevouringOne,
			Claws_InfestedKerrigan,
			NeedleSpines_Normal,
			NeedleSpines_HunterKiller,
			KaiserBlades_Normal,
			KaiserBlades_Torrasque,
			ToxicSpores_Broodling,
			Spines,
			Spines_Harvest,
			AcidSpray_Unused,
			AcidSpore_Normal,
			AcidSpore_Kukulza,
			GlaveWurm_Normal,
			GlaveWurm_Kukulza,
			Venom_Unused,
			Venom_Hero_Unused,
			SeekerSpores,
			SubterraneanTentacle,
			Suicide_InfestedTerran,
			Suicide_Scourge,
			Parasite,
			SpawnBroodlings,
			Ensnare,
			DarkSwarm,
			Plague,
			Consume,
			ParticleBeam,
			ParticleBeam_Harvest,
			PsiBlades_Normal,
			PsiBlades_Fenix,
			PhaseDisruptor_Normal,
			PhaseDisruptor_Fenix,
			PsiAssault_Normal,
			PsiAssault_Hero,
			PsionicShockwave_Normal,
			PsionicShockwave_Hero,
			Unknown72,
			DualPhotonBlasters_Normal,
			AntiMatterMissiles_Normal,
			DualPhotonBlasters_Mojo,
			AnitMatterMissiles_Mojo,
			PhaseDisruptorCannon_Normal,
			PhaseDisruptorCannon_Danimoth,
			PulseCannon,
			STSPhotonCannon,
			STAPhotonCannon,
			Scarab,
			StasisField,
			PsiStorm,
			WarpBlades_Zeratul,
			WarpBlades_DarkTemplarHero,
			Missiles_Unused,
			LaserBattery1_Unused,
			TormentorMissiles_Unused,
			Bombs_Unused,
			RaiderGun_Unused,
			LaserBattery2_Unused,
			LaserBattery3_Unused,
			DualPhotonBlasters_Unused,
			FlechetteGrenade_Unused,
			TwinAutocannons_FloorTrap,
			HellfireMissilePack_WallTrap,
			FlameThrower_WallTrap,
			HellfireMissilePack_FloorTrap,
			
			COUNT
		};
	}
}
namespace SC = StarCraft;

namespace BroodWar {
	namespace Technology {
		enum : u8 {
			StimPacks,
			Lockdown,
			EMPShockwave,
			SpiderMines,
			ScannerSweep,
			SiegeMode,
			DefensiveMatrix,
			Irradiate,
			YamatoGun,
			CloakingField,
			PersonnelCloaking,
			Burrowing,
			Infestation,
			SpawnBroodling,
			DarkSwarm,
			Plague,
			Consume,
			Ensnare,
			Parasite,
			PsionicStorm,
			Hallucination,
			Recall,
			StasisField,
			ArchonWarp,
			Restoration,
			DisruptionWeb,
			Unused26,
			MindControl,
			DarkArchonMeld,
			Feedback,
			OpticalFlare,
			Maelstorm,
			LurkerAspect,
			Unused33,
			Healing,
			Unused35,
			Unused36,
			Unused37,
			Unused38,
			Unused39,
			Unused40,
			Unused41,
			Unused42,
			Unused43,
			
			COUNT
		};
	}
	
	namespace Upgrade {
		enum : u8 {
			TerranInfantryArmor,
			TerranVehiclePlating,
			TerranShipPlating,
			ZergCarapace,
			ZergFlyerCaparace,
			ProtossArmor,
			ProtossPlating,
			TerranInfantryWeapons,
			TerranVehicleWeapons,
			TerranShipWeapons,
			ZergMeleeAttacks,
			ZergMissileAttacks,
			ZergFlyerAttacks,
			ProtossGroundWeapons,
			ProtossAirWeapons,
			ProtossPlasmaShields,
			U238Shells,
			IonThrusters,
			BurstLasers_Unused,
			TitanReactor,
			OcularImplants,
			MoebiusReactor,
			ApolloReactor,
			ColossusReactor,
			VentralSacs,
			Antennae,
			PneumatizedCarapace,
			MetabolicBoost,
			AdrenalGlands,
			MuscularAugments,
			GroovedSpines,
			GameteMeiosis,
			MetasynapticNode,
			SingularityCharge,
			LegEnhancements,
			ScarabDamage,
			ReaverCapacity,
			GraviticDrive,
			SensorArray,
			GraviticBoosters,
			KhaydarinAmulet,
			ApialSensors,
			GraviticThrusters,
			CarrierCapacity,
			KhaydarinCore,
			Unknown45,
			Unknown46,
			ArgusJewel,
			Unknown48,
			ArgusTalisman,
			Unknown50,
			CaduceusReactor,
			ChitinousPlating,
			AnabolicSynthesis,
			CharonBooster,
			Unknown55,
			Unknown56,
			Unknown57,
			Unknown58,
			Unknown59,
			Unknown60,
			
			COUNT
		};
	}
	
	namespace Weapon {
		enum : u8 {
			GaussRifle_Normal,
			GaussRifle_JimRaynor,
			C10ConcussionRifle_Normal,
			C10ConcussionRifle_SarahKerrigan,
			FragmentationGrenade_Normal,
			FragmentationGrenade_JimRaynor,
			SpiderMines,
			TwinAutocannons_Normal,
			HellfireMissilePack_Normal,
			TwinAutocannons_AlanSchezar,
			HellfireMissilePack_AlanSchezar,
			ArcliteCannon_Normal,
			ArcliteCannon_EdmundDuke,
			FusionCutter,
			FusionCutter_Harvest,
			GeminiMissiles_Normal,
			BurstLasers_Normal,
			GeminiMissiles_TomKazansky,
			BurstLasers_TomKazansky,
			ATSLaserBattery_Normal,
			ATALaserBattery_Normal,
			ATSLaserBattery_Hero,
			ATALaserBattery_Hero,
			ATSLaserBattery_Hyperion,
			ATALaserBattery_Hyperion,
			FlameThrower_Normal,
			FlameThrower_GuiMontag,
			ArcliteShockCannon_Normal,
			ArcliteShockCannon_EdmundDuke,
			LongboltMissiles,
			YamatoGun,
			NuclearMissile,
			Lockdown,
			EMPShockwave,
			Irradiate,
			Claws_Normal,
			Claws_DevouringOne,
			Claws_InfestedKerrigan,
			NeedleSpines_Normal,
			NeedleSpines_HunterKiller,
			KaiserBlades_Normal,
			KaiserBlades_Torrasque,
			ToxicSpores_Broodling,
			Spines,
			Spines_Harvest,
			AcidSpray_Unused,
			AcidSpore_Normal,
			AcidSpore_Kukulza,
			GlaveWurm_Normal,
			GlaveWurm_Kukulza,
			Venom_Unused,
			Venom_Hero_Unused,
			SeekerSpores,
			SubterraneanTentacle,
			Suicide_InfestedTerran,
			Suicide_Scourge,
			Parasite,
			SpawnBroodlings,
			Ensnare,
			DarkSwarm,
			Plague,
			Consume,
			ParticleBeam,
			ParticleBeam_Harvest,
			PsiBlades_Normal,
			PsiBlades_Fenix,
			PhaseDisruptor_Normal,
			PhaseDisruptor_Fenix,
			PsiAssault_Normal,
			PsiAssault_Hero,
			PsionicShockwave_Normal,
			PsionicShockwave_Hero,
			Unknown72,
			DualPhotonBlasters_Normal,
			AntiMatterMissiles_Normal,
			DualPhotonBlasters_Mojo,
			AnitMatterMissiles_Mojo,
			PhaseDisruptorCannon_Normal,
			PhaseDisruptorCannon_Danimoth,
			PulseCannon,
			STSPhotonCannon,
			STAPhotonCannon,
			Scarab,
			StasisField,
			PsiStorm,
			WarpBlades_Zeratul,
			WarpBlades_DarkTemplarHero,
			Missiles_Unused,
			LaserBattery1_Unused,
			TormentorMissiles_Unused,
			Bombs_Unused,
			RaiderGun_Unused,
			LaserBattery2_Unused,
			LaserBattery3_Unused,
			DualPhotonBlasters_Unused,
			FlechetteGrenade_Unused,
			TwinAutocannons_FloorTrap,
			HellfireMissilePack_WallTrap,
			FlameThrower_WallTrap,
			HellfireMissilePack_FloorTrap,
			NeutronFlare,
			DisruptionWeb,
			Restoration,
			HaloRockets,
			CorrosiveAcid,
			MindControl,
			Feedback,
			OpticalFlare,
			Maelstrom,
			SubterraneanSpines,
			GaussRifle0_Unused,
			WarpBlades_Normal,
			C10ConcussionRifle_SamirDuran,
			C10ConcussionRifle_InfestedDuran,
			DualPhotonBlasters_Artanis,
			AntiMatterMissiles_Artanis,
			C10ConcussionRifle_AlexeiStukov,
			GaussRifle1_Unused,
			GaussRifle2_Unused,
			GaussRifle3_Unused,
			GaussRifle4_Unused,
			GaussRifle5_Unused,
			GaussRifle6_Unused,
			GaussRifle7_Unused,
			GaussRifle8_Unused,
			GaussRifle9_Unused,
			GaussRifle10_Unused,
			GaussRifle11_Unused,
			GaussRifle12_Unused,
			GaussRifle13_Unused,
			
			COUNT
		};
	}
}