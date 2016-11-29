#! /usr/bin/env python

import re, uuid, optparse, json, codecs, os, copy, collections

class ModeDef(object):
	def __init__(self, pattern=r'.+'):
		self.regex = re.compile(pattern)

	def match_mode(self, mode):
		return (self.regex.match(mode) != None)

	def update_modes(self, modes):
		pass

class ChangeModeDef(ModeDef):
	def __init__(self, pattern=r'.+', change_mode=None):
		ModeDef.__init__(self, pattern)
		self.change_mode = change_mode

	def update_modes(self, modes):
		if self.change_mode != None:
			modes[-1] = self.change_mode

class NestModeDef(ChangeModeDef):
	def __init__(self, pattern=r'.+', change_mode=None, nest_mode=''):
		ChangeModeDef.__init__(self, pattern, change_mode)
		self.nest_mode = nest_mode

	def update_modes(self, modes):
		ChangeModeDef.update_modes(self, modes)
		modes.append(self.nest_mode)

class PopModeDef(ModeDef):
	def update_modes(self, modes):
		del modes[-1]



class TokenDef(object):
	def __init__(self, name='Unknown', pattern=r'.', modes=[(r'.+',None)], ignorable=False):
		self.name = name
		self.regex = re.compile(pattern)
		self.modes = modes
		self.ignorable = ignorable


class Token(object):
	def __init__(self, tokendef=None, mode='', value='', info={}):
		self.tokendef = tokendef
		self.mode = mode
		self.value = value
		self.info = info

	def __repr__(self):
		return '<Token instance at %s:\n\tname\t= %s\n\tmode\t= %s\n\tvalue\t= %s\n\tinfo\t= %s\n>' % (hex(id(self)), self.tokendef.name, self.mode, self.value, self.info)

class Tokenizer(object):
	whitespace = re.compile(r'\s+')

	def __init__(self, source):
		self.modes = ['main']
		self.source = source
		self.offset = 0
		self.definitions = []

	def add_definition(self, definition):
		self.definitions.append(definition)

	def _next(self):
		match_whitespace = Tokenizer.whitespace.match(self.source, self.offset)
		if match_whitespace:
			self.offset += len(match_whitespace.group(0))
		mode = self.modes[-1]
		# mode_matches = 0
		for check_def in self.definitions:
			for check_mode in check_def.modes:
				if check_mode.match_mode(mode):
					# mode_matches += 1
					match = check_def.regex.match(self.source, self.offset)
					if match:
						check_mode.update_modes(self.modes)
						self.offset += len(match.group(0))
						return Token(check_def, mode, match.group(0), match.groupdict())
		print 'No TokenDef matches mode:\n\t%s\nFor:\n\t%s' % (self.modes, self.source[self.offset:min(self.offset+10,len(self.source)-1)])
		return None

	def next(self, skip_ignorables=True):
		token = self._next()
		if skip_ignorables:
			while token.tokendef.ignorable:
				token = self._next()
		return token

singleLineCommentDef = TokenDef(
	name	= 'SingleLineComment',
	pattern	= r'(?m)//(?P<COMMENT_TEXT>.*)$',
	modes	= [
		ModeDef(
			pattern	= r'.+'
		)
	],
	ignorable = True
)

multiLineCommentDef = TokenDef(
	name	= 'MultiLineComment',
	pattern	= r'(?m)/\*(?P<COMMENT_TEXT>.*?)\*/',
	modes	= [
		ModeDef(
			pattern	= r'.+'
		)
	],
	ignorable = True
)

objectStartDef = TokenDef(
	name	= 'ObjectStart',
	pattern	= r'\{',
	modes	= [
		NestModeDef(
			pattern		= r'main$',
			nest_mode	= 'object'
		),
		NestModeDef(
			pattern		= r'object\.value$',
			change_mode = 'object.value.end',
			nest_mode	= 'object'
		),
		NestModeDef(
			pattern		= r'array$',
			change_mode	= 'array.value',
			nest_mode	= 'object'
		)
	]
)

numberDef = TokenDef(
	name	= 'Number',
	pattern	= r'\d+(?:\.\d+)?(?![a-zA-Z0-9\.])',
	modes	= [
		ChangeModeDef(
			pattern		= r'object\.value$',
			change_mode	= 'object.value.end'
		)
	]
)
identifierDef = TokenDef(
	name	= 'Identifier',
	pattern	= r'[^\s;{}"(),]+',
	modes	= [
		ChangeModeDef(
			pattern		= r'object$',
			change_mode	= 'object.key'
		),
		ChangeModeDef(
			pattern		= r'object\.value$',
			change_mode	= 'object.value.end'
		),
		ChangeModeDef(
			pattern		= r'array$',
			change_mode = 'array.value'
		)
	]
)

assignDef = TokenDef(
	name	= 'Assign',
	pattern	= r'=',
	modes	= [
		ChangeModeDef(
			pattern		= r'object\.key$',
			change_mode	= 'object.value'
		)
	]
)

semicolonDef = TokenDef(
	name	= 'Semicolon',
	pattern	= r';',
	modes	= [
		ChangeModeDef(
			pattern		= r'object\.value\.end$',
			change_mode	= 'object'
		)
	]
)

objectEndDef = TokenDef(
	name	= 'ObjectEnd',
	pattern	= r'\}',
	modes	= [
		PopModeDef(
			pattern		= r'object$'
		)
	]
)

stringDef = TokenDef(
	name	= 'String',
	pattern	= r'"(?P<TEXT>(?:[^"\\]|\\.)*)"',
	modes	= [
		ChangeModeDef(
			pattern		= r'object\.value$',
			change_mode	= 'object.value.end'
		),
		ChangeModeDef(
			pattern		= r'array',
			change_mode	= 'array.value'
		),
		ChangeModeDef(
			pattern		= r'object$',
			change_mode	= 'object.key'
		)
	]
)

arrayStartDef = TokenDef(
	name	= 'ArrayStart',
	pattern	= r'\(',
	modes	= [
		NestModeDef(
			pattern		= r'object\.value$',
			change_mode	= 'object.value.end',
			nest_mode	= 'array'
		)
	]
)

commaDef = TokenDef(
	name	= 'Comma',
	pattern	= r'\,',
	modes	= [
		ChangeModeDef(
			pattern		= r'array\.value$',
			change_mode	= 'array',
		)
	]
)

arrayEndDef = TokenDef(
	name	= 'ArrayEnd',
	pattern	= r'\)',
	modes	= [
		PopModeDef(
			pattern	= r'array$'
		),
		PopModeDef(
			pattern = r'array\.value$'
		)
	]
)

eofDef = TokenDef(
	name	= 'EndOfFile',
	pattern	= r'$',
	modes	= [
		PopModeDef(
			pattern = r'main$'
		)
	]
)

class PBXObj(object):
	def __init__(self):
		self.properties = {}

	def load(self, properties):
		self.properties = properties

	def __getattr__(self, name):
		if not name in self.properties:
			raise AttributeError("%s instance has no attribute '%s'" % (self.__class__.__name__, name))
		return self.properties[name]

	def type(self):
		return self.__class__.__name__

	def info(self):
		return collections.OrderedDict({
			'type':self.type()
		})

	def identifier_label(self):
		return self.type()

	def pbx_writable(self):
		writable = dict(self.properties)
		writable['isa'] = self.type()
		return writable

	def pbx_write(self):
		writable = self.pbx_writable()
		return pbx_write(writable)

class PBXObject(PBXObj):
	def __init__(self):
		PBXObj.__init__(self)
		self.pbxproj = None
		self.parents = None
		self.identifier = None

	def load(self, pbxproj, parent, identifier, properties={}):
		PBXObj.load(self, properties)
		self.pbxproj = pbxproj
		self.identifier = identifier
		self.add_parent(parent)

	def info(self):
		info = PBXObj.info(self)
		info['identifier'] = self.identifier
		return info

	def flatten(self, objects):
		new = False
		if not self.type() in objects:
			objects[self.type()] = {}
			new = True
		if not self.identifier in objects[self.type()]:
			objects[self.type()][self.identifier] = self
			new = True
		return new

	def add_parent(self, parent):
		if self.parents == None:
			self.parents = []
		self.parents.append(parent)

class PBXObjectUnknown(PBXObject):
	def __init__(self):
		PBXObj.__init__(self)
		self.obj_type = None

	def load(self, pbxproj, parent, obj_type, identifier, properties):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		self.obj_type = obj_type

	def type(self):
		return self.obj_type

class PBXProject(PBXObject):
	def __init__(self):
		PBXObject.__init__(self)
		self.main_group = None
		self.product_group = None
		self.build_configurations = None
		self.targets = None
		self.project_refs = None

	def load(self, pbxproj, parent, identifier, properties):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		main_group_id = self.properties.pop('mainGroup')
		if main_group_id == None:
			raise
		self.main_group = pbxproj.get_object(main_group_id, self)
		if self.main_group == None:
			raise
		self.product_group = None
		if 'productRefGroup' in self.properties:
			product_group = self.properties.pop('productRefGroup')
			self.product_group = pbxproj.get_object(product_group, self)
		build_configurations_id = self.properties.pop('buildConfigurationList')
		if build_configurations_id == None:
			raise
		self.build_configurations = pbxproj.get_object(build_configurations_id, self)
		if self.build_configurations == None:
			raise
		target_ids = self.properties.pop('targets')
		if target_ids == None:
			raise
		if not len(target_ids) > 0:
			raise
		self.targets = []
		for target_id in target_ids:
			target = pbxproj.get_object(target_id, self)
			if target == None:
				raise
			self.targets.append(target)
		self.project_refs = None
		if 'projectReferences' in self.properties:
			project_refs = self.properties.pop('projectReferences')
			self.project_refs = []
			for project_ref in project_refs:
				info = dict(project_ref)
				for key,value in info.iteritems():
					other_proj = pbxproj.get_object(value, self)
					if other_proj == None:
						raise
					info[key] = other_proj
				self.project_refs.append(info)

	def display_name(self):
		return self.pbxproj.name

	def flatten(self, objects):
		if PBXObject.flatten(self, objects):
			self.main_group.flatten(objects)
			self.build_configurations.flatten(objects)
			for target in self.targets:
				target.flatten(objects)
			if self.project_refs != None:
				for info in self.project_refs:
					for key,value in info.iteritems():
						value.flatten(objects)

	def info(self):
		info = PBXObject.info(self)
		info['versions'] = collections.OrderedDict({
			'compatability':self.compatibilityVersion
		})
		info['targets'] = []
		for target in self.targets:
			info['targets'].append(collections.OrderedDict((
					('name',target.name),
					('identifier',target.identifier)
				)))
		info['build_configurations'] = []
		for config in self.build_configurations.configurations:
			info['build_configurations'].append(collections.OrderedDict((
					('name',config.name),
					('identifier',config.identifier)
				)))
			if config.name == self.build_configurations.defaultConfigurationName:
				info['build_configurations'][-1]['default'] = True
		info['files'] = []
		for child in self.main_group.children:
			info['files'].append(collections.OrderedDict((
					('name',child.display_name()),
					('identifier',child.identifier)
				)))
		return info

	def identifier_label(self):
		return 'Project object'

	def pbx_writable(self):
		writable = PBXObject.pbx_writable(self)
		writable['mainGroup'] = PBXIdentifierWriter(self.main_group)
		if self.product_group != None:
			writable['productRefGroup'] = PBXIdentifierWriter(self.product_group)
		writable['buildConfigurationList'] = PBXIdentifierWriter(self.build_configurations)
		writable['targets'] = []
		for target in self.targets:
			writable['targets'].append(PBXIdentifierWriter(target))
		if self.project_refs != None:
			writable['projectReferences'] = []
			for project_ref in self.project_refs:
				info = dict(project_ref)
				for key,value in info.iteritems():
					info[key] = PBXIdentifierWriter(value)
				writable['projectReferences'].append(info)
		return writable

class PBXGroup(PBXObject):
	def __init__(self):
		PBXObject.__init__(self)
		self.children = None

	def load(self, pbxproj, parent, identifier, properties):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		child_ids = self.properties.pop('children')
		if child_ids == None:
			raise
		self.children = []
		for child_id in child_ids:
			child = pbxproj.get_object(child_id, self)
			if child == None:
				raise
			self.children.append(child)

	def add_child(self, child):
		if self.children == None:
			self.children = []
		self.children.append(child)
		child.add_parent(self)
	def insert_child(self, child, index):
		self.children.insert(index, child)
		child.add_parent(self)
	def insert_child_before(self, child, before):
		self.insert_child(child, self.children.index(before))
	def insert_child_after(self, child, after):
		self.insert_child(child, self.children.index(after)+1)

	def flatten(self, objects):
		if PBXObject.flatten(self, objects):
			for child in self.children:
				child.flatten(objects)

	def display_name(self):
		if 'name' in self.properties:
			return self.name
		if 'path' in self.properties:
			return self.path
		return 'Unknown Group'

	def info(self):
		info = PBXObject.info(self)
		info['name'] = self.display_name()
		if 'path' in self.properties:
			info['path'] = self.path
		info['files'] = []
		for child in self.children:
			info['files'].append(collections.OrderedDict((
					('name',child.display_name()),
					('identifier',child.identifier)
				)))
		return info

	def identifier_label(self):
		if 'name' in self.properties or 'path' in self.properties:
			return self.display_name()
		return None

	def pbx_writable(self):
		writable = PBXObject.pbx_writable(self)
		writable['children'] = []
		for child in self.children:
			writable['children'].append(PBXIdentifierWriter(child))
		return writable

class PBXVariantGroup(PBXGroup):
	pass

class PBXFileReference(PBXObject):
	def display_name(self):
		if 'name' in self.properties:
			return self.name
		else:
			return self.path

	def info(self):
		info = PBXObject.info(self)
		info['name'] = self.display_name()
		info['path'] = self.path
		info['type'] = self.lastKnownFileType
		return info

	def identifier_label(self):
		return self.display_name()

	def pbx_write(self):
		return pbx_flatten(PBXObject.pbx_write(self))

class XCConfigurationList(PBXObject):
	def __init__(self):
		PBXObject.__init__(self)
		self.configurations = None

	def load(self, pbxproj, parent, identifier, properties):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		build_config_ids = self.properties.pop('buildConfigurations')
		if build_config_ids == None:
			raise
		self.configurations = []
		for build_config_id in build_config_ids:
			build_config = pbxproj.get_object(build_config_id, self)
			if build_config == None:
				raise
			self.configurations.append(build_config)

	def flatten(self, objects):
		if PBXObject.flatten(self, objects):
			for config in self.configurations:
				config.flatten(objects)

	def identifier_label(self):
		parent = self.parents[0]
		return 'Build configuration list for %s "%s"' % (parent.type(), parent.display_name())

	def pbx_writable(self):
		writable = PBXObject.pbx_writable(self)
		writable['buildConfigurations'] = []
		for build_config in self.configurations:
			writable['buildConfigurations'].append(PBXIdentifierWriter(build_config))
		return writable

class XCBuildConfiguration(PBXObject):
	def info(self):
		info = PBXObject.info(self)
		info['settings'] = working.buildSettings
		return info

	def identifier_label(self):
		return self.name

class PBXTarget(PBXObject):
	def __init__(self):
		PBXObject.__init__(self)
		self.build_configurations = None
		self.product_reference = None
		self.dependencies = None
		self.build_phases = None
		self.build_rules = None

	def load(self, pbxproj, parent, identifier, properties):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		build_configs_id = self.properties.pop('buildConfigurationList')
		if build_configs_id == None:
			raise
		self.build_configurations = pbxproj.get_object(build_configs_id, self)
		if self.build_configurations == None:
			raise
		if 'productReference' in self.properties:
			product_ref_id = self.properties.pop('productReference')
			self.product_reference = pbxproj.get_object(product_ref_id, self)
			if self.product_reference == None:
				raise
		dependency_ids = self.properties.pop('dependencies')
		if dependency_ids == None:
			raise
		self.dependencies = []
		for dependency_id in dependency_ids:
			dependency = pbxproj.get_object(dependency_id, self)
			if dependency == None:
				raise
			self.dependencies.append(dependency)
		build_phase_ids = self.properties.pop('buildPhases')
		if build_phase_ids == None:
			raise
		self.build_phases = []
		for build_phase_id in build_phase_ids:
			build_phase = pbxproj.get_object(build_phase_id, self)
			if build_phase == None:
				raise
			self.build_phases.append(build_phase)
		if 'buildRules' in self.properties:
			build_rule_ids = self.properties.pop('buildRules')
			self.build_rules = []
			for build_rules_id in build_rule_ids:
				build_rules = pbxproj.get_object(build_rules_id, self)
				if build_rules == None:
					raise
				self.build_rules.append(build_rules)

	def add_build_rule(self, rule):
		if self.build_rules == None:
			self.build_rules = []
		self.build_rules.append(rule)
		rule.add_parent(self)

	def add_build_phase(self, phase):
		self.build_phases.append(phase)
		phase.add_parent(self)
	def insert_build_phase(self, phase, index):
		self.build_phases.insert(index, phase)
		phase.add_parent(self)

	def display_name(self):
		return self.name

	def flatten(self, objects):
		if PBXObject.flatten(self, objects):
			self.build_configurations.flatten(objects)
			if self.product_reference:
				self.product_reference.flatten(objects)
			for dependency in self.dependencies:
				dependency.flatten(objects)
			for phase in self.build_phases:
				phase.flatten(objects)
			if self.build_rules != None:
				for rule in self.build_rules:
					rule.flatten(objects)

	def info(self):
		info = PBXObject.info(self)
		info['name'] = self.name
		info['product'] = self.productName
		info['build_configurations'] = []
		for config in self.build_configurations.configurations:
			info['build_configurations'].append(collections.OrderedDict((
					('name',config.name),
					('identifier',config.identifier)
				)))
			if config.name == self.build_configurations.defaultConfigurationName:
				info['build_configurations'][-1]['default'] = True
		info['build_phases'] = []
		for phase in self.build_phases:
			info['build_phases'].append(collections.OrderedDict((
					('name',phase.display_name()),
					('identifier',phase.identifier)
				)))
		if self.build_rules != None:
			info['build_rules'] = []
			for rule in self.build_rules:
				info['build_rules'].append(collections.OrderedDict((
						('name',rule.display_name()),
						('identifier',rule.identifier)
					)))
		return info

	def identifier_label(self):
		return self.name

	def pbx_writable(self):
		writable = PBXObject.pbx_writable(self)
		writable['buildConfigurationList'] = PBXIdentifierWriter(self.build_configurations)
		if self.product_reference:
			writable['productReference'] = PBXIdentifierWriter(self.product_reference)
		writable['dependencies'] = []
		for dependency in self.dependencies:
			writable['dependencies'].append(PBXIdentifierWriter(dependency))
		writable['buildPhases'] = []
		for phase in self.build_phases:
			writable['buildPhases'].append(PBXIdentifierWriter(phase))
		if self.build_rules != None:
			writable['buildRules'] = []
			for rule in self.build_rules:
				writable['buildRules'].append(PBXIdentifierWriter(rule))
		return writable

class PBXNativeTarget(PBXTarget):
	pass

class PBXAggregateTarget(PBXTarget):
	pass

class PBXTargetDependency(PBXObject):
	def __init__(self):
		PBXObject.__init__(self)
		self.target = None
		self.proxy = None

	def load(self, pbxproj, parent, identifier, properties):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		self.target = None
		if 'target' in self.properties:
			target_id = self.properties.pop('target')
			self.target = pbxproj.get_object(target_id, self)
		if 'targetProxy' in self.properties:
			target_proxy_id = self.properties.pop('targetProxy')
			if target_proxy_id == None:
				raise
			self.proxy = pbxproj.get_object(target_proxy_id, self)
			if self.proxy == None:
				raise

	def flatten(self, objects):
		if PBXObject.flatten(self, objects) and self.proxy != None:
			self.proxy.flatten(objects)

	def pbx_writable(self):
		writable = PBXObject.pbx_writable(self)
		if self.target != None:
			writable['target'] = PBXIdentifierWriter(self.target)
		if self.proxy != None:
			writable['targetProxy'] = PBXIdentifierWriter(self.proxy)
		return writable

class PBXContainerItemProxy(PBXObject):
	def __init__(self):
		PBXObject.__init__(self)
		self.container_portal = None

	def load(self, pbxproj, parent, identifier, properties):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		container_portal_id = self.properties.pop('containerPortal')
		if container_portal_id == None:
			raise
		self.container_portal = pbxproj.get_object(container_portal_id, self)
		if self.container_portal == None:
			raise

	def flatten(self, objects):
		if PBXObject.flatten(self, objects):
			self.container_portal.flatten(objects)

	def pbx_writable(self):
		writable = PBXObject.pbx_writable(self)
		writable['containerPortal'] = PBXIdentifierWriter(self.container_portal)
		return writable

class PBXBuildPhase(PBXObject):
	def __init__(self):
		PBXObject.__init__(self)
		self.files = None

	def load(self, pbxproj, parent, identifier, properties):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		file_ids = self.properties.pop('files')
		if file_ids == None:
			raise
		self.files = []
		for file_id in file_ids:
			f = pbxproj.get_object(file_id, self)
			if f == None:
				raise
			self.files.append(f)

	def add_file(self, f):
		if self.files == None:
			self.files = []
		self.files.append(f)
		f.add_parent(self)
	def add_file_ref(self, ref):
		f = PBXBuildFile()
		f.file = ref
		self.pbxproj.add_object(f)
		self.add_file(f)

	def flatten(self, objects):
		if PBXObject.flatten(self, objects):
			for f in self.files:
				f.flatten(objects)

	def display_name(self):
		return 'Unknown'

	def info(self):
		info = PBXObject.info(self)
		info['name'] = self.display_name()
		info['files'] = []
		for ref in self.files:
			info['files'].append(collections.OrderedDict((
					('name',ref.file.display_name()),
					('identifier',ref.identifier)
				)))
		return info

	def identifier_label(self):
		return self.display_name()

	def pbx_writable(self):
		writable = PBXObject.pbx_writable(self)
		writable['files'] = []
		for f in self.files:
			writable['files'].append(PBXIdentifierWriter(f))
		return writable

class PBXShellScriptBuildPhase(PBXBuildPhase):
	def display_name(self):
		return self.name

	def info(self):
		info = PBXBuildPhase.info(self)
		info['shell_path'] = self.shellPath
		info['shell_script'] = self.shellScript
		# del info['files']
		return info

class PBXResourcesBuildPhase(PBXBuildPhase):
	def display_name(self):
		return 'Resources'

class PBXSourcesBuildPhase(PBXBuildPhase):
	def display_name(self):
		return 'Sources'

class PBXFrameworksBuildPhase(PBXBuildPhase):
	def display_name(self):
		return 'Frameworks'

class PBXCopyFilesBuildPhase(PBXBuildPhase):
	def display_name(self):
		return 'Copy Files'

class PBXBuildFile(PBXObject):
	def __init__(self):
		PBXObject.__init__(self)
		self.file = None

	def load(self, pbxproj, parent, identifier, properties=None):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		if not properties == None:
			file_ref_id = self.properties.pop('fileRef')
			if file_ref_id == None:
				raise
			self.file = pbxproj.get_object(file_ref_id, self)
			if self.file == None:
				raise

	def flatten(self, objects):
		if PBXObject.flatten(self, objects):
			self.file.flatten(objects)

	def info(self):
		info = PBXObject.info(self)
		info['name'] = self.file.name
		info['path'] = self.file.path
		info['type'] = self.file.lastKnownFileType
		if 'settings' in self.properties:
			info['settings'] = self.settings
		return info

	def identifier_label(self):
		parent = self.parents[0]
		return '%s in %s' % (self.file.identifier_label(), parent.display_name())

	def pbx_writable(self):
		writable = PBXObject.pbx_writable(self)
		writable['fileRef'] = PBXIdentifierWriter(self.file)
		return writable

	def pbx_write(self):
		return pbx_flatten(PBXObject.pbx_write(self))

class PBXBuildRule(PBXObject):
	def display_name(self):
		return 'Build Rule (%s)' % self.filePatterns

class PBXReferenceProxy(PBXObject):
	def __init__(self):
		PBXObject.__init__(self)
		self.remote_ref = None

	def load(self, pbxproj, parent, identifier, properties):
		PBXObject.load(self, pbxproj, parent, identifier, properties)
		remote_ref_id = self.properties.pop('remoteRef')
		if remote_ref_id == None:
			raise
		self.remote_ref = pbxproj.get_object(remote_ref_id, self)
		if self.remote_ref == None:
			raise

	def flatten(self, objects):
		if PBXObject.flatten(self, objects):
			self.remote_ref.flatten(objects)

	def display_name(self):
		return self.path

	def identifier_label(self):
		return self.display_name()

	def pbx_writable(self):
		writable = PBXObject.pbx_writable(self)
		writable['remoteRef'] = PBXIdentifierWriter(self.remote_ref)
		return writable




class PBXIdentifierWriter:
	def __init__(self, obj=None):
		self.obj = obj
	def pbx_write(self):
		identifier = self.obj.identifier
		if hasattr(self.obj, 'identifier_label') and self.obj.identifier_label() != None:
			identifier += ' /* %s */' % (self.obj.identifier_label())
		return identifier

class PBXObjectWriter(dict):
	def pbx_write(self):
		result = '{'
		types = sorted(self.keys())
		id_writer = PBXIdentifierWriter()
		for obj_type in types:
			result += '\n/* Begin %s section */\n' % obj_type
			ids = sorted(self[obj_type].keys())
			for i in ids:
				obj = self[obj_type][i]
				id_writer.obj = obj
				result += '\t%s = %s;\n' % (id_writer.pbx_write(), pbx_indent(obj.pbx_write()))
			result += '/* End %s section */\n' % obj_type
		result += '}'
		return result

RE_FLATTEN = re.compile(r'\n\t*')
RE_SEMICOLON = re.compile(r'(;)')
def pbx_flatten(text):
	result = RE_FLATTEN.sub('', text)
	return RE_SEMICOLON.sub(r'\1 ', result)
RE_NEWLINES = re.compile(r'(\n)(?!/\*)')
def pbx_indent(text):
	return RE_NEWLINES.sub(r'\1\t', text)
RE_BASIC_STRING = re.compile(r'^[a-zA-Z0-9_./]+$')
def pbx_write(obj):
	result = ''
	if hasattr(obj, 'pbx_write'):
		result = obj.pbx_write()
	elif isinstance(obj, str) or isinstance(obj, unicode):
		if RE_BASIC_STRING.match(obj):
			result = obj
		else:
			result = '"%s"' % obj # WARNING: DO PROPER DECODE OF STRINGS ON LOAD AND THEN ENCODE ON WRITE
	elif isinstance(obj, dict):
		result = '{\n'
		keys = sorted(obj.keys())
		if 'isa' in keys:
			keys.remove('isa')
			keys.insert(0, 'isa')
		for key in keys:
			result += '\t%s = %s;\n' % (pbx_write(key), pbx_indent(pbx_write(obj[key])))
		result += '}'
	elif isinstance(obj, list):
		result = '(\n'
		for value in obj:
			result += '\t%s,\n' % pbx_indent(pbx_write(value))
		result += ')'
	else:
		return repr(obj)
		# raise
	return result

class PBXPROJ(PBXObj):
	def __init__(self):
		PBXObj.__init__(self)
		self.objects = None
		self.root = None
		self.name = None

	def read(self, name, filepath):
		self.name = name

		f = codecs.open(filepath, 'r', encoding='utf-8')
		source = f.read()
		f.close()

		tokenizer = Tokenizer(source)
		tokenizer.add_definition(singleLineCommentDef)
		tokenizer.add_definition(multiLineCommentDef)
		tokenizer.add_definition(objectStartDef)
		tokenizer.add_definition(numberDef)
		tokenizer.add_definition(identifierDef)
		tokenizer.add_definition(assignDef)
		tokenizer.add_definition(semicolonDef)
		tokenizer.add_definition(objectEndDef)
		tokenizer.add_definition(stringDef)
		tokenizer.add_definition(arrayStartDef)
		tokenizer.add_definition(commaDef)
		tokenizer.add_definition(arrayEndDef)
		tokenizer.add_definition(eofDef)

		self.properties = self.parse_value(tokenizer)
		# print json.dumps(self.properties, indent=2)
		objects = self.properties.pop('objects')
		if objects == None:
			raise
		self.objects = objects
		root = self.properties.pop('rootObject')
		if root == None:
			raise
		self.root = self.get_object(root, self)
		# print self.properties

	def display_name(self):
		return self.name

	def pbx_writable(self):
		writable = {}
		writable.update(self.properties)
		writable['objects'] = PBXObjectWriter()
		writable['rootObject'] = PBXIdentifierWriter(self.root)
		self.root.flatten(writable['objects'])
		return writable

	def pbx_write(self):
		result = '// !$*UTF8*$!\n'
		result += PBXObj.pbx_write(self) + '\n'
		return result

	def save(self, filepath):
		data = pbx_write(self)

		f = codecs.open(filepath, 'w', encoding='utf-8')
		f.write(data)
		f.close()

	def _identifier(self):
		rawUUID = uuid.uuid4()
		return ''.join('%02X' % ord(l) for l in rawUUID.bytes[:12])

	def new_identifier(self):
		identifier = self._identifier()
		while identifier in self.objects:
			identifier = self._identifier()
		return identifier

	def get_object(self, identifier, parent):
		obj = self.objects[identifier]
		if not isinstance(obj, PBXObject):
			if 'isa' in obj:
				obj_type = obj.pop('isa')
				if obj_type in globals():
					objclass = globals()[obj_type]
					model = objclass()
					self.objects[identifier] = model
					model.load(self, parent, identifier, obj)
					obj = model
				else:
					print 'Missing isa: %s' % obj_type
					print obj
					model = PBXObjectUnknown()
					self.objects[identifier] = model
					model.load(self, parent, obj_type, identifier, obj)
					obj = model
			else:
				model = PBXObject()
				self.objects[identifier] = model
				model.load(self, identifier, obj)
				obj = model
		else:
			obj.parents.append(parent)
		return obj

	def add_object(self, obj):
		obj.pbxproj = self
		if obj.identifier == None:
			obj.identifier = self.new_identifier()
		self.objects[obj.identifier] = obj

	def parse_value(self, tokenizer, token=None):
		if token == None:
			token = tokenizer.next()
		if token.tokendef.name == 'Number':
			if '.' in token.value:
				return float(token.value)
			else:
				return int(token.value)
		elif token.tokendef.name == 'String':
			return token.info['TEXT']
		elif token.tokendef.name == 'Identifier':
			return token.value
		elif token.tokendef.name == 'ObjectStart':
			obj = {}
			token = tokenizer.next()
			while token.tokendef.name != 'ObjectEnd':
				if token.tokendef.name != 'Identifier' and token.tokendef.name != 'String':
					raise
				key = token.value
				if token.tokendef.name == 'String':
					key = token.info['TEXT']
				token = tokenizer.next()
				if token.tokendef.name != 'Assign':
					raise
				value = self.parse_value(tokenizer)
				obj[key] = value
				token = tokenizer.next()
				if token.tokendef.name != 'Semicolon':
					raise
				token = tokenizer.next() 
			return obj
		elif token.tokendef.name == 'ArrayStart':
			array = []
			token = tokenizer.next()
			while token.tokendef.name != 'ArrayEnd':
				value = self.parse_value(tokenizer, token)
				array.append(value)
				token = tokenizer.next()
				if token.tokendef.name == 'Comma':
					token = tokenizer.next()
			return array
		print token
		raise

	def info(self):
		info = self.root.info()
		info['versions']['archive'] = self.properties['archiveVersion']
		info['versions']['object'] = self.properties['objectVersion']
		return info



VERSION = (0,0,1)
LONG_VERSION = 'v%d.%d.%d' % VERSION

class MyFormatter(optparse.IndentedHelpFormatter):
	def format_description(self, description):
		lines = description.split('\n')
		for i,line in enumerate(lines):
			if not len(line) > 0:
				lines[i] = '\n'
			else:
				lines[i] = optparse.IndentedHelpFormatter.format_description(self, line)
		return ''.join(lines)

parser = optparse.OptionParser(
	usage		= '%prog <xcproj> <specifiers ...> <command ...> [options]',
	version		= '%%prog %s' % LONG_VERSION,
	description	= """Read and manipulate Xcode project files.

Specifiers:
  file <file> [file <file> ...]
  config <config>
  target <target>
  target <target> config <config>
  target <target> phase <phase>
  target <target> phase <phase> file <file>

General Commands:
  info

Project Commands:
  add <path>
  delete

Config Commands:
  clone <clone name>
  get <setting> [index]
  lookup <setting> [index]
  set <setting> <type> <value>
  set <setting> array [<type> <value>]
  set <setting> item <index> <type> <value>
  insert <setting> <index> <type> <value>
  append <setting> <type> <value>
  delete <setting> [index]

Phase Commands:
  assign <specifiers ...>
  remove <file>""",

	formatter	= MyFormatter()
)

parser.add_option(
	'-s',
	'--symbol',
	action	= 'store',
	type	= 'string',
	dest	= 'identifier_symbol',
	default	= '@',
	nargs	= 1,
	help	= 'Symbol used at the beginning of other fields to mark them as identifiers [Default: @]',
	metavar = 'SYMBOL'
)
parser.add_option(
	'-i',
	'--indent',
	action	= 'store',
	type	= 'int',
	dest	= 'indent',
	default	= None,
	nargs	= 1,
	help	= 'Number of spaces used to indent',
	metavar = 'SPACES'
)
parser.add_option(
	'-o',
	'--output',
	action	= 'store',
	type	= 'string',
	dest	= 'output',
	default	= None,
	nargs	= 1,
	help	= 'Output file path',
	metavar = 'FILE'
)

def parse_specifiers(options, project, specifiers):
	result = project
	while len(specifiers) and specifiers[0] in ('file','config','target','phase'):
		if not len(specifiers) > 1:
			raise
		specifier = specifiers.pop(0)
		check = specifiers.pop(0)
		is_id = check.startswith(options.identifier_symbol)
		if is_id:
			check = check[1:]
		if specifier == 'file':
			if isinstance(result, PBXBuildPhase):
				for ref in result.files:
					if (is_id and ref.identifier == check) or (not is_id and ref.file.display_name() == check):
						result = ref
						break
				else:
					raise
			elif isinstance(result, PBXGroup) or isinstance(result, PBXPROJ):
				group = result
				if isinstance(group, PBXPROJ):
					group = group.root.main_group
				for g in group.children:
					if (is_id and g.identifier == check) or (not is_id and g.display_name() == check):
						result = g
						break
				else:
					raise
			# elif isinstance(result, FILE):
			else:
				raise
		elif specifier == 'config':
			configs = []
			if isinstance(result, PBXPROJ):
				configs = proj.root.build_configurations.configurations
			elif isinstance(result, PBXTarget):
				configs = result.build_configurations.configurations
			else:
				raise
			for config in configs:
				if (is_id and config.identifier == check) or (not is_id and config.name == check):
					result = config
					break
			else:
				raise
		elif specifier == 'target':
			if not isinstance(result, PBXPROJ):
				raise
			for target in result.root.targets:
				if (is_id and target.identifier == check) or (not is_id and target.name == check):
					result = target
					break
			else:
				raise
		elif specifier == 'phase':
			if not isinstance(result, PBXTarget):
				raise
			for phase in result.build_phases:
				if (is_id and phase.identifier == check) or (not is_id and phase.display_name() == check):
					result = phase
					break
			else:
				raise
	return result

def parse_value(specifier, exclude_types=[]):
	if not len(specifier) > 0:
		raise
	valtype = specifier.pop(0)
	if valtype in exclude_types:
		raise
	if not len(specifier) > 0:
		raise
	value = specifier.pop(0)
	if valtype == 'int':
		try:
			value = int(value)
		except:
			raise
	elif valtype == 'float':
		try:
			value = float(value)
		except:
			raise
	elif not valtype == 'string':
		raise
	return value

def get_config(obj):
	if isinstance(obj, XCBuildConfiguration):
		return obj.buildSettings
	elif isinstance(obj, PBXBuildFile):
		return obj.settings
	else:
		raise

def lookup_setting(check, options, specifiers):
	if not len(specifiers) > 0:
		raise
	setting = specifiers.pop(0)
	index = None
	if len(specifiers) > 0:
		index = specifiers.pop(0)
		try:
			index = int(index)
		except:
			raise
		if index < 0:
			raise
	def get_setting(working):
		value = get_config(working).get(setting)
		if not value == None:
			if isinstance(value,list):
				if index == None:
					return value
				else:
					if index >= len(value):
						raise
					return value[index]
			else:
				return value
	value = None
	while value == None and len(check):
		value = get_setting(check.pop(0))
	return value

def handle_output(value, options):
	separators = (',',':')
	if options.indent != None:
		separators = (',',': ')
	print json.dumps(value, indent=options.indent, separators=separators)

def valid_object(obj, types):
	valid = False
	for t in types:
		if isinstance(obj, t):
			valid = True
			break
	return valid

def main():
	options,args = parser.parse_args()

	if not len(args) > 0:
		parser.error('Missing <xcproj>')
	if not len(args) > 1:
		parser.error('Missing <specifiers...>')

	inp = os.path.normpath(args.pop(0))
	if not os.path.exists(inp):
		raise
	name = os.path.splitext(os.path.basename(inp))[0]
	pbxproj = os.path.join(inp, 'project.pbxproj')
	proj = PBXPROJ()
	proj.read(name, pbxproj)

	working = parse_specifiers(options, proj, args)

	if not len(args) > 0:
		parser.error('Missing <command...>')
	command = args.pop(0)

	save = False

	if command == 'info':
		if len(args) > 0:
			raise
		handle_output(working.info(), options)
	elif command == 'clone':
		if not valid_object(working, (XCBuildConfiguration,)):
			raise
		if not len(args) > 0:
			raise
		properties = copy.deepcopy(working.properties)
		properties['name'] = args.pop(0)
		clone = XCBuildConfiguration()
		clone.pbxproj = working.pbxproj
		clone.parents = list(working.parents)
		clone.identifier = clone.pbxproj.new_identifier()
		clone.properties = properties
		# clone.load(working.pbxproj, None, working.pbxproj.new_identifier(), properties)
		for parent in clone.parents:
			parent.configurations.append(clone)
		save = True
	elif command == 'get' or command == 'lookup':
		if not valid_object(working, (XCBuildConfiguration,PBXBuildFile)):
			raise
		check = [working]
		if command == 'lookup' and isinstance(working, XCBuildConfiguration):
			for config in proj.root.build_configurations.configurations:
				if config.name == working.name and not config.identifier == working.identifier:
					check.append(config)
					break
		value = lookup_setting(check, options, args)
		if len(args) > 0:
			raise
		if not value == None:
			handle_output(value, options)
	elif command == 'set':
		if not valid_object(working, (XCBuildConfiguration,PBXBuildFile)):
			raise
		if not len(args) > 0:
			raise
		setting = args.pop(0)
		if not len(args) > 0:
			raise
		array = False
		index = None
		if args[0] == 'item':
			del args[0]
			if not len(args) > 0:
				raise
			index = args.pop(0)
			try:
				index = int(index)
			except:
				raise
			if index < 0:
				raise
		elif args[0] == 'array':
			del args[0]
			array = True
		if array and not len(args) > 0:
			value = []
		else:
			value = parse_value(args)
			if len(args) > 0:
				raise
			if array:
				value = [value]
		settings = get_config(working)
		if index == None:
			settings[setting] = value
		else:
			if not setting in settings:
				raise
			update = settings[setting]
			if not isinstance(update, list):
				raise
			if index >= len(update):
				raise
			update[index] = value
		save = True
		print settings
	elif command == 'insert' or command == 'append':
		if not valid_object(working, (XCBuildConfiguration,PBXBuildFile)):
			raise
		if not len(args) > 0:
			raise
		setting = args.pop(0)
		index = None
		if command == 'insert':
			if not len(args) > 0:
				raise
			index = args.pop(0)
			try:
				index = int(index)
			except:
				raise
			if index < 0:
				raise
		value = parse_value(args)
		if len(args) > 0:
			raise
		setting = get_config(working)
		if not setting in settings:
			raise
		array = settings[setting]
		if not isinstance(array, list):
			raise
		if index == None:
			array.append(value)
		else:
			if index >= len(array):
				raise
			array.insert(index, value)
		save = True
		print settings
	elif command == 'delete':
		if not valid_object(working, (XCBuildConfiguration,PBXBuildFile)):
			raise
		if not len(args) > 0:
			raise
		setting = args.pop(0)
		index = None
		if len(args) > 0:
			index = args.pop(0)
			try:
				index = int(index)
			except:
				raise
			if index < 0:
				raise
		if len(args) > 0:
			raise
		settings = get_config(working)
		if index == None and setting in settings:
			del settings[setting]
		else:
			array = settings[setting]
			if index >= len(array):
				raise
			del array[index]
		save = True
		print settings
	elif command == 'assign':
		if not valid_object(working, PBXBuildPhase):
			raise
		assign = parse_specifiers(options, proj, args)
		if not isinstance(assign, PBXFileReference):
			raise
		ref = PBXBuildFile(proj, proj.new_identifier())
		proj.properties['objects'][ref.identifier] = ref
		ref.file = assign
		working.files.append(ref)
		save = True
		print working.info()
	elif command == 'remove':
		if not valid_object(working, PBXBuildPhase):
			raise
		if not len(args) > 0:
			raise
		check = args.pop(0)
		is_id = check.startswith(options.identifier_symbol)
		if is_id:
			check = check[1:]
		for i in range(len(working.files)):
			ref = working.files[i]
			if (is_id and ref.identifier == check) or (not is_id and ref.file.display_name() == check):
				del working.files[i]
				break
		else:
			raise
		save = True
		print working.info()
	else:
		raise

	if save:
		output = inp
		if options.output:
			output = options.output
		proj.save(output)

if __name__ == '__main__':
	main()

