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
struct COLOR
{
    float4 COLOR : COLOR0;
};
    struct TARGET
{
    float4 Target : SV_Target;
};

void PS(in POSITION pos : SV_Position,
        in COLOR color : COLOR0,
        in COORD texcoord : TEXCOORD0,
        out TARGET target: SV_Target)
{
    float4 color1 = TEXTURE2D.Sample(SAMPLERSTATE, texcoord.Coord);
    
    if (color1.r >= 1.f &&
        color1.g <= 0.f &&
        color1.b >= 1.f)        discard;
    
    target.Target = color1 * color.COLOR;
}