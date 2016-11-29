from PyBXPROJ import *
import os


QT_BIN_PATH = '/Users/zachzahos/Applications/Qt551/5.5/clang_64/bin/'

QT_QMAKE = os.path.join(QT_BIN_PATH, 'qmake')
QT_MOC = os.path.join(QT_BIN_PATH, 'moc')


os.system(QT_QMAKE + ' -spec macx-xcode')


inp = './SCMap.xcodeproj/'
if not os.path.exists(inp):
	raise
name = os.path.splitext(os.path.basename(inp))[0]
pbxproj = os.path.join(inp, 'project.pbxproj')
proj = PBXPROJ()
proj.read(name, pbxproj)

rule = PBXBuildRule()
rule.properties = {
	"compilerSpec":"com.apple.compilers.proxy.script",
	"filePatterns":"*.h",
	"fileType":"pattern.proxy",
	"isEditable":1,
	"outputFiles":[
		"${DERIVED_FILE_DIR}/moc_${INPUT_FILE_BASE}.cpp",
	],
	"script":QT_MOC + " ${INPUT_FILE_PATH} -o ${DERIVED_FILE_DIR}/moc_${INPUT_FILE_BASE}.cpp"
}
proj.add_object(rule)

target = None
for t in proj.root.targets:
	if isinstance(t, PBXNativeTarget) and t.name == 'SCMap':
		target = t
		target.add_build_rule(rule)
		break
else:
	raise

sourcesGroup = PBXGroup()
sourcesGroup.properties = {
	"path":"Sources",
	"sourceTree":"<group>"
}
sourcesGroup.children = []
proj.add_object(sourcesGroup)

resGroup = PBXGroup()
resGroup.properties = {
	"path":"Resources",
	"sourceTree":"<group>"
}
proj.add_object(resGroup)

libGroup = PBXGroup()
libGroup.properties = {
	"path":"Libraries",
	"sourceTree":"<group>"
}
proj.add_object(libGroup)

proj.root.main_group.insert_child(sourcesGroup, 0)
proj.root.main_group.insert_child(resGroup, 1)
proj.root.main_group.insert_child(libGroup, 2)


sourcesPhase = PBXSourcesBuildPhase()
sourcesPhase.properties = {
	"buildActionMask":2147483647,
	"name":"Compile Sources",
	"runOnlyForDeploymentPostprocessing":0
}
proj.add_object(sourcesPhase)

target.insert_build_phase(sourcesPhase, 1)

def build_sources(group, path):
	files = []
	folders = []
	for name in os.listdir(path):
		full = os.path.join(path,name)
		if os.path.isfile(full):
			files.append(name)
		elif os.path.isdir(full):
			folders.append(name)
	for name in files:
		kind = None
		build = False
		if name.endswith('.h'):
			kind = 'sourcecode.c.h'
			try:
				with open(os.path.join(path,name),'r') as f:
					contents = f.read()
					if 'Q_OBJECT' in contents:
						build = True
			except:
				pass
		elif name.endswith('.cpp'):
			kind = 'sourcecode.cpp.cpp'
			build = True
		ref = PBXFileReference()
		ref.properties = {
			"lastKnownFileType":kind,
			"path":name,
			"sourceTree":"<group>"
		}
		proj.add_object(ref)
		group.add_child(ref)
		if build:
			sourcesPhase.add_file_ref(ref)
	for name in folders:
		child = PBXGroup()
		child.properties = {
			"path":name,
			"sourceTree":"<group>"
		}
		child.children = []
		proj.add_object(child)
		group.add_child(child)
		build_sources(child, os.path.join(path,name))
build_sources(sourcesGroup, "./Sources")


copy = PBXCopyFilesBuildPhase()
copy.properties = {
	"buildActionMask":2147483647,
	"dstPath":"",
	"dstSubfolderSpec":16,
	"runOnlyForDeploymentPostprocessing":0
}
proj.add_object(copy)

target.add_build_phase(copy)


resources = [
	'badlands.cv5',
	'badlands.grp',
	'badlands.vf4',
	'badlands.vr4',
	'badlands.vx4',
	'badlands.wpe',
	'dddata.bin',
	'scenario.chk'
]
for name in resources:
	ref = PBXFileReference()
	ref.properties = {
		"lastKnownFileType":"file",
		"path":name,
		"sourceTree":"<group>"
	}
	proj.add_object(ref)

	resGroup.add_child(ref)

	copy.add_file_ref(ref)

frameworksPhase = None
for phase in target.build_phases:
	if isinstance(phase, PBXFrameworksBuildPhase):
		frameworksPhase = phase
		break

libraries = [
	{
		'name':'SFmpqapi',
		'headers':[
			'poppack.h',
			'pshpack1.h',
			'SFmpqapi.h',
			'windows.h'
		],
		'binaries':[
			('SFmpq.dylib','compiled.mach-o.dylib')
		]
	}
]

for lib in libraries:
	group = PBXGroup()
	group.properties = {
		"path":lib["name"],
		"sourceTree":"<group>"
	}
	proj.add_object(group)

	libGroup.add_child(group)

	for header in lib["headers"]:
		ref = PBXFileReference()
		ref.properties = {
			"lastKnownFileType":"sourcecode.c.h",
			"path":header,
			"fileEncoding":4,
			"sourceTree":"<group>"
		}
		proj.add_object(ref)

		group.add_child(ref)

	for binary,kind in lib["binaries"]:
		ref = PBXFileReference()
		ref.properties = {
			"lastKnownFileType":kind,
			"path":binary,
			"sourceTree":"<group>"
		}
		proj.add_object(ref)

		group.add_child(ref)

		frameworksPhase.add_file_ref(ref)

	if len(lib["binaries"]):
		for config in target.build_configurations.configurations:
			if not 'LIBRARY_SEARCH_PATHS' in config.buildSettings:
				config.buildSettings['LIBRARY_SEARCH_PATHS'] = ["$(inherited)"]
			config.buildSettings['LIBRARY_SEARCH_PATHS'].append("$(PROJECT_DIR)/Libraries/" + lib["name"])

scms = PBXFileReference()
scms.properties = {
	"lastKnownFileType":"wrapper.framework",
	"path":"libSCMS.framework",
	"sourceTree":"SOURCE_ROOT"
}
proj.add_object(scms)

for group in proj.root.main_group.children:
	if isinstance(group, PBXGroup) and 'name' in group.properties and group.name == 'Frameworks':
		group.insert_child(scms, 0)
		break
else:
	raise

frameworksPhase.add_file_ref(scms)

for config in proj.root.build_configurations.configurations:
	config.buildSettings['FRAMEWORK_SEARCH_PATHS'].append(os.path.abspath('.'))

for config in target.build_configurations.configurations:
	config.buildSettings['GCC_INLINES_ARE_PRIVATE_EXTERN'] = 'NO'
	config.buildSettings['GCC_SYMBOLS_PRIVATE_EXTERN'] = 'NO'

proj.save(pbxproj)

