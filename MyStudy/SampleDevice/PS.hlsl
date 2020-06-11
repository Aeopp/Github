Texture2D TEXTURE2D : register(t0);
SamplerState SAMPLERSTATE : register(s0);

struct POSITION
{
    float4 Pos : SV_Position;
};
struct COORD 
{
    float2 Coord : TEXCOORD0;
};
struct TARGET
{
    float4 Target : SV_Target;
};

void PS(in POSITION pos : SV_Position,
        in COORD texcoord : TEXCOORD0,
        out TARGET target: SV_Target)
{
    target.Target = TEXTURE2D.Sample(SAMPLERSTATE, texcoord.Coord);
}