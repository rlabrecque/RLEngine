#include "PCH.hpp"
#include "CInput.hpp"

InputClass::InputClass() {
	m_directInput = nullptr;
	m_keyboard = nullptr;
	m_mouse = nullptr;
}

InputClass::InputClass(const InputClass&) {
}

InputClass::~InputClass() {
}

bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight) {
	HRESULT result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_mouseX = 0;
	m_mouseY = 0;

	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, nullptr);
	if(FAILED(result)) {
		return false;
	}

	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, nullptr);
	if(FAILED(result)) {
		return false;
	}

	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(result)) {
		return false;
	}

	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result)) {
		return false;
	}

	result = m_keyboard->Acquire();
	if(FAILED(result)) {
		return false;
	}

	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, nullptr);
	if(FAILED(result)) {
		return false;
	}

	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if(FAILED(result)) {
		return false;
	}

	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(result)) {
		return false;
	}

	result = m_mouse->Acquire();
	if(FAILED(result)) {
		return false;
	}

	return true;
}

void InputClass::Shutdown() {
	if(m_mouse != nullptr) {
		m_mouse->Unacquire();
		m_mouse->Release();
	}

	if(m_keyboard != nullptr) {
		m_keyboard->Unacquire();
		m_keyboard->Release();
	}

	if(m_directInput != nullptr) {
		m_directInput->Release();
	}

	return;
}

bool InputClass::Frame() {
	bool result;

	result = ReadKeyboard();
	if(!result) {
		return false;
	}

	result = ReadMouse();
	if(!result) {
		return false;
	}

	ProcessInput();

	return true;
}

bool InputClass::ReadKeyboard() {
	HRESULT result;
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if(FAILED(result)) {
		if(result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
			m_keyboard->Acquire();
		}
		else {
			return false;
		}
	}

	return true;
}

bool InputClass::ReadMouse() {
	HRESULT result;

	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if(FAILED(result)) {
		if(result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
			m_mouse->Acquire();
		}
		else {
			return false;
		}
	}

	return true;
}

void InputClass::ProcessInput() {
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	if(m_mouseX < 0) {
		m_mouseX = 0;
	}
	if(m_mouseY < 0) {
		m_mouseY = 0;
	}

	if(m_mouseX > m_screenWidth) {
		m_mouseX = m_screenWidth;
	}
	if(m_mouseY > m_screenHeight) {
		m_mouseY = m_screenHeight;
	}

	return;
}

void InputClass::GetMouseLocation(int& mouseX, int& mouseY) {
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	return;
}

bool InputClass::IsEscapePressed() {
	if(m_keyboardState[DIK_ESCAPE] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsLeftArrowPressed() {
	if(m_keyboardState[DIK_LEFT] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsRightArrowPressed() {
	if(m_keyboardState[DIK_RIGHT] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsUpArrowPressed() {
	if(m_keyboardState[DIK_UP] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsDownArrowPressed() {
	if(m_keyboardState[DIK_DOWN] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsPgUpPressed() {
	if(m_keyboardState[DIK_PGUP] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsPgDownPressed() {
	if(m_keyboardState[DIK_PGDN] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsWPressed() {
	if(m_keyboardState[DIK_W] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsAPressed() {
	if(m_keyboardState[DIK_A] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsSPressed() {
	if(m_keyboardState[DIK_S] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsDPressed() {
	if(m_keyboardState[DIK_D] & 0x80) {
		return true;
	}

	return false;
}

bool InputClass::IsZPressed() {
	if(m_keyboardState[DIK_Z] & 0x80) {
		return true;
	}

	return false;
}