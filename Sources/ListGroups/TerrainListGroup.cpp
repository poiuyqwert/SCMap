//
//  TerrainListGroup.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-12.
//
//

#include "TerrainListGroup.h"
#include "Map.h"

#include <libSCMS/Types.h>
#include <libSCMS/CHK.h>
#include <libSCMS/CHKSectionERA.h>

#include <QStandardItem>


struct TileGroupType {
	char const *name;
	struct {
		u16 start;
		u16 end;
	} megatileGroups;
	struct {
		struct {
			u8 start;
			u8 end;
		} normal;
		struct {
			u8 start;
			u8 end;
		} messy;
	} tiles;
};

struct TerrainType {
	char const *name;
	TileGroupType tileGroups[13];
};

TerrainType TerrainTypes[CHKSectionERA::COUNT] = {
	{
		.name = "Badlands",
		.tileGroups = {
			{
				.name = "Rocky Ground",
				.megatileGroups = {
					.start = 12,
					.end = 13
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 11
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Asphalt",
				.megatileGroups = {
					.start = 16,
					.end = 17
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Structure",
				.megatileGroups = {
					.start = 18,
					.end = 19
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Grass",
				.megatileGroups = {
					.start = 10,
					.end = 11
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 6
					},
					.messy = {
						.start = 8,
						.end = 10
					}
				}
			},
			{
				.name = "Grass",
				.megatileGroups = {
					.start = 8,
					.end = 9
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 6
					},
					.messy = {
						.start = 8,
						.end = 10
					}
				}
			},
			{
				.name = "Water",
				.megatileGroups = {
					.start = 6,
					.end = 7
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "High Dirt",
				.megatileGroups = {
					.start = 4,
					.end = 5
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Mud",
				.megatileGroups = {
					.start = 20,
					.end = 21
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Dirt",
				.megatileGroups = {
					.start = 2,
					.end = 3
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{}
		}
	},
	{
		.name = "Space Platform",
		.tileGroups = {
			{
				.name = "Elevated Catwalk",
				.megatileGroups = {
					.start = 20,
					.end = 21
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 3
					},
					.messy = {
						.start = 5,
						.end = 6
					}
				}
			},
			{
				.name = "High Plating",
				.megatileGroups = {
					.start = 10,
					.end = 11
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 14
					}
				}
			},
			{
				.name = "High Platform",
				.megatileGroups = {
					.start = 8,
					.end = 9
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 14
					}
				}
			},
			{
				.name = "Solar Array",
				.megatileGroups = {
					.start = 12,
					.end = 13
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 0
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Plating",
				.megatileGroups = {
					.start = 6,
					.end = 7
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 14
					}
				}
			},
			{
				.name = "Dark Platform",
				.megatileGroups = {
					.start = 16,
					.end = 17
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 14
					}
				}
			},
			{
				.name = "Platform",
				.megatileGroups = {
					.start = 4,
					.end = 5
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 14
					}
				}
			},
			{
				.name = "Rusty Pit",
				.megatileGroups = {
					.start = 18,
					.end = 19
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 9
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Low Platform",
				.megatileGroups = {
					.start = 14,
					.end = 15
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 14
					}
				}
			},
			{
				.name = "Space",
				.megatileGroups = {
					.start = 2,
					.end = 3
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 0
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{}
		}
	},
	{
		.name = "Installation",
		.tileGroups = {
			{
				.name = "Bottomless Pit",
				.megatileGroups = {
					.start = 12,
					.end = 13
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 0
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Sunstructure Panels",
				.megatileGroups = {
					.start = 14,
					.end = 15
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 3
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Plating",
				.megatileGroups = {
					.start = 10,
					.end = 11
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Substructure Plating",
				.megatileGroups = {
					.start = 4,
					.end = 5
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Roof",
				.megatileGroups = {
					.start = 8,
					.end = 9
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 0
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Floor",
				.megatileGroups = {
					.start = 6,
					.end = 7
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 0
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Substructure",
				.megatileGroups = {
					.start = 2,
					.end = 3
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 0
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{}
		}
	},
	{
		.name = "Ashworld",
		.tileGroups = {
			{
				.name = "High Shale",
				.megatileGroups = {
					.start = 12,
					.end = 13
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 7
					},
					.messy = {
						.start = 9,
						.end = 10
					}
				}
			},
			{
				.name = "High Lava",
				.megatileGroups = {
					.start = 8,
					.end = 9
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 9
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "High Dirt",
				.megatileGroups = {
					.start = 6,
					.end = 7
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 7
					},
					.messy = {
						.start = 9,
						.end = 14
					}
				}
			},
			{
				.name = "Broken Rock",
				.megatileGroups = {
					.start = 16,
					.end = 17
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 12
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Shale",
				.megatileGroups = {
					.start = 10,
					.end = 11
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 7
					},
					.messy = {
						.start = 9,
						.end = 10
					}
				}
			},
			{
				.name = "Lava",
				.megatileGroups = {
					.start = 4,
					.end = 5
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 9
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Dirt",
				.megatileGroups = {
					.start = 2,
					.end = 3
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 7
					},
					.messy = {
						.start = 9,
						.end = 14
					}
				}
			},
			{
				.name = "Magma",
				.megatileGroups = {
					.start = 14,
					.end = 15
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 7
					},
					.messy = {
						.start = 9,
						.end = 14
					}
				}
			},
			{}
		}
	},
	{
		.name = "Jungle",
		.tileGroups = {
			{
				.name = "High Temple",
				.megatileGroups = {
					.start = 24,
					.end = 25
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 4
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "High Raised Jungle",
				.megatileGroups = {
					.start = 22,
					.end = 23
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Ruins",
				.megatileGroups = {
					.start = 20,
					.end = 21
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Jungle",
				.megatileGroups = {
					.start = 18,
					.end = 19
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Dirt",
				.megatileGroups = {
					.start = 4,
					.end = 5
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Temple",
				.megatileGroups = {
					.start = 16,
					.end = 17
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 4
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Raised Jungle",
				.megatileGroups = {
					.start = 12,
					.end = 13
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Ruins",
				.megatileGroups = {
					.start = 14,
					.end = 15
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Rocky Ground",
				.megatileGroups = {
					.start = 10,
					.end = 11
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 11
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Jungle",
				.megatileGroups = {
					.start = 8,
					.end = 9
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Mud",
				.megatileGroups = {
					.start = 26,
					.end = 27
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Dirt",
				.megatileGroups = {
					.start = 2,
					.end = 3
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Water",
				.megatileGroups = {
					.start = 6,
					.end = 7
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			
		}
	},
	{
		.name = "Desert",
		.tileGroups = {
			{
				.name = "High Compound",
				.megatileGroups = {
					.start = 24,
					.end = 25
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 4
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "High Sandy Sunken Pit",
				.megatileGroups = {
					.start = 22,
					.end = 23
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Crags",
				.megatileGroups = {
					.start = 20,
					.end = 21
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Sand Dunes",
				.megatileGroups = {
					.start = 18,
					.end = 19
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Dirt",
				.megatileGroups = {
					.start = 4,
					.end = 5
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Compund",
				.megatileGroups = {
					.start = 16,
					.end = 17
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 4
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Sandy Sunken Pit",
				.megatileGroups = {
					.start = 12,
					.end = 13
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Crags",
				.megatileGroups = {
					.start = 14,
					.end = 15
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Rocky Ground",
				.megatileGroups = {
					.start = 10,
					.end = 11
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 11
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Sand Dunes",
				.megatileGroups = {
					.start = 8,
					.end = 9
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Dried Mud",
				.megatileGroups = {
					.start = 26,
					.end = 27
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Dirt",
				.megatileGroups = {
					.start = 2,
					.end = 3
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Tar",
				.megatileGroups = {
					.start = 6,
					.end = 7
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 2
					},
					.messy = {
						.start = 4,
						.end = 6
					}
				}
			},
			
		}
	},
	{
		.name = "Arctic",
		.tileGroups = {
			{
				.name = "High Outpost",
				.megatileGroups = {
					.start = 24,
					.end = 25
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 2
					},
					.messy = {
						.start = 4,
						.end = 5
					}
				}
			},
			{
				.name = "High Water",
				.megatileGroups = {
					.start = 22,
					.end = 23
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "High Grass",
				.megatileGroups = {
					.start = 20,
					.end = 21
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Dirt",
				.megatileGroups = {
					.start = 18,
					.end = 19
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Snow",
				.megatileGroups = {
					.start = 4,
					.end = 5
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Outpost",
				.megatileGroups = {
					.start = 16,
					.end = 17
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 2
					},
					.messy = {
						.start = 4,
						.end = 5
					}
				}
			},
			{
				.name = "Water",
				.megatileGroups = {
					.start = 12,
					.end = 13
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Grass",
				.megatileGroups = {
					.start = 14,
					.end = 15
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Rocky Snow",
				.megatileGroups = {
					.start = 10,
					.end = 11
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Dirt",
				.megatileGroups = {
					.start = 8,
					.end = 9
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Moguls",
				.megatileGroups = {
					.start = 26,
					.end = 27
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 14
					}
				}
			},
			{
				.name = "Snow",
				.megatileGroups = {
					.start = 2,
					.end = 3
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Ice",
				.megatileGroups = {
					.start = 6,
					.end = 7
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			
		}
	},
	{
		.name = "Twilight",
		.tileGroups = {
			{
				.name = "High Basilica",
				.megatileGroups = {
					.start = 24,
					.end = 25
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 4
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "High Sunken Ground",
				.megatileGroups = {
					.start = 22,
					.end = 23
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Flagstones",
				.megatileGroups = {
					.start = 20,
					.end = 21
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Crushed Rock",
				.megatileGroups = {
					.start = 18,
					.end = 19
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "High Dirt",
				.megatileGroups = {
					.start = 4,
					.end = 5
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Basilica",
				.megatileGroups = {
					.start = 16,
					.end = 17
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 4
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Sunken Ground",
				.megatileGroups = {
					.start = 12,
					.end = 13
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Flagstones",
				.megatileGroups = {
					.start = 14,
					.end = 15
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Crevices",
				.megatileGroups = {
					.start = 10,
					.end = 11
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 11
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			{
				.name = "Crushed Rock",
				.megatileGroups = {
					.start = 8,
					.end = 9
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 7,
						.end = 12
					}
				}
			},
			{
				.name = "Mud",
				.megatileGroups = {
					.start = 26,
					.end = 27
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 8
					},
					.messy = {
						.start = 10,
						.end = 14
					}
				}
			},
			{
				.name = "Dirt",
				.megatileGroups = {
					.start = 2,
					.end = 3
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 7
					},
					.messy = {
						.start = 9,
						.end = 14
					}
				}
			},
			{
				.name = "Water",
				.megatileGroups = {
					.start = 6,
					.end = 7
				},
				.tiles = {
					.normal = {
						.start = 0,
						.end = 5
					},
					.messy = {
						.start = 0,
						.end = 0
					}
				}
			},
			
		}
	}
};

TerrainListGroup::TerrainListGroup(QStandardItem *parent)
	: ListGroup(parent, "Terrain")
{

}

void TerrainListGroup::update(Map *map) {
	QStandardItem *root = this->get_root();
	root->removeRows(0, root->rowCount());
	if (map) {
		CHK *chk = map->get_chk();
		CHKSectionERA *era = chk->get_section<CHKSectionERA>();
		u16 tileset = era->get_tileset();
		for (int i = 0; i < 13; i++) {
			if (TerrainTypes[tileset].tileGroups[i].name == nullptr) {
				break;
			}
			QStandardItem *terrain = new QStandardItem(TerrainTypes[tileset].tileGroups[i].name);
			terrain->setFlags(terrain->flags() & ~Qt::ItemIsEditable);
			root->appendRow(terrain);
		}
	}
}

void TerrainListGroup::itemSelected(MapSubWindow *, QStandardItem *) {

}
