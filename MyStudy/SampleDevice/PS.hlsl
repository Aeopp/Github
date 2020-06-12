
//float4 main(in float4 Pixel : SV_Position) : SV_TARGET
//{
//    return float4(1.0f, 1.0f, 1.0f, 1.0f);
//};

void PS(in float4 p: SV_Position,
out float4 c : SV_Target)
{
    c = float4(1, 0, 0, 1);
}