#include "Sample.h"

bool Sample::Render() {
	RECT rt = m_rtClient;
	m_Write.Draw(0, L"test1", rt, D2D1::ColorF(1, 1, 1, 1));
	rt.top += 30;
	m_Write.Draw(2, L"test2", rt, D2D1::ColorF(1, 0, 0, 0.5f));
	return true;
}
