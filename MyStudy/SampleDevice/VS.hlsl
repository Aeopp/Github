// ���ؽ� ���̴��� ����������ŭ ȣ��Ǹ� �ݵ�� float4 �� ��ȯ�ؾ���
// ���� ���̴��� �ݵ�� ������ ��ġ SV_POSITION �� ��ȯ�ؾ���

//float4 VS(in float3 pos : POSITION) : SV_POSITION
//{
//    return float4(pos, 1.f);
//};

struct VS_IN
{
    float3 Pos: POSITION;
};
struct VS_OUT
{
    float4 Pos : SV_Position;
};
struct PS_OUT
{
    float4 Pos : SV_Target;
};
VS_OUT VS(in VS_IN pos : POSITION) : SV_Position
{
    VS_OUT VertexOut;
    VertexOut.Pos = float4(pos.Pos.x, pos.Pos.y, pos.Pos.z, 1);
    return VertexOut;
};

PS_OUT PS(in VS_OUT VertexOut : SV_Position) :SV_Target
{
    PS_OUT PixelOut;
    PixelOut.Pos = float4(1, 0, 0, 1);
    return PixelOut;
}

