#include "IOLogWrapper.hpp"
#include "ParamsUnion.hpp"

namespace org_pqrs_Karabiner {
  ParamsUnion::ParamsUnion(const Params_KeyboardEventCallBack& p) : type(KEYBOARD)
  {
    params_.params_KeyboardEventCallBack = Params_KeyboardEventCallBack::alloc(p);
  }

  ParamsUnion::ParamsUnion(const Params_UpdateEventFlagsCallback& p) : type(UPDATE_FLAGS)
  {
    params_.params_UpdateEventFlagsCallback = Params_UpdateEventFlagsCallback::alloc(p);
  }

  ParamsUnion::ParamsUnion(const Params_KeyboardSpecialEventCallback& p) : type(KEYBOARD_SPECIAL)
  {
    params_.params_KeyboardSpecialEventCallback = Params_KeyboardSpecialEventCallback::alloc(p);
  }

  ParamsUnion::ParamsUnion(const Params_RelativePointerEventCallback& p) : type(RELATIVE_POINTER)
  {
    params_.params_RelativePointerEventCallback = Params_RelativePointerEventCallback::alloc(p);
  }

  ParamsUnion::ParamsUnion(const Params_ScrollWheelEventCallback& p) : type(SCROLL_WHEEL)
  {
    params_.params_ScrollWheelEventCallback = Params_ScrollWheelEventCallback::alloc(p);
  }

  ParamsUnion::ParamsUnion(const Params_Wait& p) : type(WAIT)
  {
    params_.params_Wait = Params_Wait::alloc(p);
  }

  ParamsUnion::ParamsUnion(const ParamsUnion& rhs) : type(rhs.type)
  {
#define NEW_PARAMS(PARAMS, CLASS) {         \
    if (rhs.PARAMS) {                       \
      PARAMS = CLASS::alloc(*(rhs.PARAMS)); \
    } else {                                \
      PARAMS = NULL;                        \
    }                                       \
}

    switch (rhs.type) {
      case KEYBOARD:
        NEW_PARAMS(params_.params_KeyboardEventCallBack, Params_KeyboardEventCallBack);
        break;
      case UPDATE_FLAGS:
        NEW_PARAMS(params_.params_UpdateEventFlagsCallback, Params_UpdateEventFlagsCallback);
        break;
      case KEYBOARD_SPECIAL:
        NEW_PARAMS(params_.params_KeyboardSpecialEventCallback, Params_KeyboardSpecialEventCallback);
        break;
      case RELATIVE_POINTER:
        NEW_PARAMS(params_.params_RelativePointerEventCallback, Params_RelativePointerEventCallback);
        break;
      case SCROLL_WHEEL:
        NEW_PARAMS(params_.params_ScrollWheelEventCallback, Params_ScrollWheelEventCallback);
        break;
      case WAIT:
        NEW_PARAMS(params_.params_Wait, Params_Wait);
        break;
      default:
        IOLOG_ERROR("ParamsUnion::~ParamsUnion() unknown type\n");
    }

#undef NEW_PARAMS
  }

  ParamsUnion::~ParamsUnion(void)
  {
#define DELETE_PARAMS(PARAMS) { \
    if (PARAMS) {               \
      delete PARAMS;            \
    }                           \
}

    switch (type) {
      case KEYBOARD:
        DELETE_PARAMS(params_.params_KeyboardEventCallBack);
        break;
      case UPDATE_FLAGS:
        DELETE_PARAMS(params_.params_UpdateEventFlagsCallback);
        break;
      case KEYBOARD_SPECIAL:
        DELETE_PARAMS(params_.params_KeyboardSpecialEventCallback);
        break;
      case RELATIVE_POINTER:
        DELETE_PARAMS(params_.params_RelativePointerEventCallback);
        break;
      case SCROLL_WHEEL:
        DELETE_PARAMS(params_.params_ScrollWheelEventCallback);
        break;
      case WAIT:
        DELETE_PARAMS(params_.params_Wait);
        break;
      default:
        IOLOG_ERROR("ParamsUnion::~ParamsUnion() unknown type\n");
    }

#undef DELETE_PARAMS
  }
}
