// 버텍스 쉐이더는 정점개수만큼 호출되며 반드시 float4 로 반환해야함
// 정점 쉐이더는 반드시 정점의 위치 SV_POSITION 을 반환해야함

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

