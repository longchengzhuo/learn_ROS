# generated from rosidl_generator_py/resource/_idl.py.em
# with input from base_interfaces_demo:srv/Addints.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Addints_Request(type):
    """Metaclass of message 'Addints_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('base_interfaces_demo')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'base_interfaces_demo.srv.Addints_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__addints__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__addints__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__addints__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__addints__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__addints__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Addints_Request(metaclass=Metaclass_Addints_Request):
    """Message class 'Addints_Request'."""

    __slots__ = [
        '_num1',
        '_num2',
    ]

    _fields_and_field_types = {
        'num1': 'int32',
        'num2': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.num1 = kwargs.get('num1', int())
        self.num2 = kwargs.get('num2', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.num1 != other.num1:
            return False
        if self.num2 != other.num2:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def num1(self):
        """Message field 'num1'."""
        return self._num1

    @num1.setter
    def num1(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num1' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'num1' field must be an integer in [-2147483648, 2147483647]"
        self._num1 = value

    @builtins.property
    def num2(self):
        """Message field 'num2'."""
        return self._num2

    @num2.setter
    def num2(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num2' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'num2' field must be an integer in [-2147483648, 2147483647]"
        self._num2 = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Addints_Response(type):
    """Metaclass of message 'Addints_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('base_interfaces_demo')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'base_interfaces_demo.srv.Addints_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__addints__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__addints__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__addints__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__addints__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__addints__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Addints_Response(metaclass=Metaclass_Addints_Response):
    """Message class 'Addints_Response'."""

    __slots__ = [
        '_num',
    ]

    _fields_and_field_types = {
        'num': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.num = kwargs.get('num', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.num != other.num:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def num(self):
        """Message field 'num'."""
        return self._num

    @num.setter
    def num(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'num' field must be an integer in [-2147483648, 2147483647]"
        self._num = value


class Metaclass_Addints(type):
    """Metaclass of service 'Addints'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('base_interfaces_demo')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'base_interfaces_demo.srv.Addints')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__addints

            from base_interfaces_demo.srv import _addints
            if _addints.Metaclass_Addints_Request._TYPE_SUPPORT is None:
                _addints.Metaclass_Addints_Request.__import_type_support__()
            if _addints.Metaclass_Addints_Response._TYPE_SUPPORT is None:
                _addints.Metaclass_Addints_Response.__import_type_support__()


class Addints(metaclass=Metaclass_Addints):
    from base_interfaces_demo.srv._addints import Addints_Request as Request
    from base_interfaces_demo.srv._addints import Addints_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
