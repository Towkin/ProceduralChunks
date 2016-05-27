<?xml version="1.0"?><doc>
<members>
<member name="T:Noise" decl="false" source="d:\c++ projects\proceduralchunksgit\proceduralchunks\noise.h" line="6">
<summary></summary>
<param name=""></param>
</member>
<member name="M:Noise.Smooth(System.Single)" decl="true" source="d:\c++ projects\proceduralchunksgit\proceduralchunks\noise.h" line="22">
<summary>Smoothing method to smooth values in range [0...1], using the polynomial function f(x) = 6x^5 - 15x^4 + 10x^3.</summary>
<param name="x">Input value to smooth.</param>
</member>
<member name="M:Noise.Lerp(System.Single,System.Single,System.Single)" decl="true" source="d:\c++ projects\proceduralchunksgit\proceduralchunks\noise.h" line="25">
<summary>Simple unclamped linear interpolation.</summary>
<param name="a">Value at t = 0.</param>
<param name="b">Value at t = 1.</param>
<param name="t">Interpolation alpha.</param>
</member>
<member name="M:Noise.IntFloorFast(System.Single)" decl="true" source="d:\c++ projects\proceduralchunksgit\proceduralchunks\noise.h" line="30">
<summary>Fast float to int mathematically correct floor conversion. Works with any float value in integer range.</summary>
<param name="x">The float value to be floored and converted to int.</param>
</member>
<member name="F:Noise.sSqrt2" decl="false" source="d:\c++ projects\proceduralchunksgit\proceduralchunks\noise.h" line="33">
<summary>Precalculated constant of the square root of 2.</summary>
</member>
<member name="M:Noise.Perlin(System.Single*,System.UInt32,System.Single,System.UInt32,System.UInt32,System.Single,System.Single)" decl="true" source="d:\c++ projects\proceduralchunksgit\proceduralchunks\noise.h" line="96">
<summary>Complex Perlin Noise method, calling multiple noise functions and returning the sum in range [-1...1].</summary>
<param name="aCoords">A C-style array containing the coordinates to calculate noise for. Must contain at least as many elements as aDimensions.</param>
<param name="aDimensions">The number of dimensions to do Perlin Noise in, can be [1], [2] or [3].</param>
<param name="aFrequency">The frequency of the first "wave". Hgih frequency = Noisy. Is used as base for later octaves.</param>
<param name="aOctaves">The number of noise calculations to run on this spot.</param>
<param name="aSeed">The seed to use when calculating each octave of noise. Note: each seed generates it's own hash-set, avoid switching too often in runtime.</param>
<param name="aLacunarity">A multiplier, multiplying the last frequency once per octave.</param>
<param name="aPersistance">How much each additional octave after the first matters.</param>
</member>
</members>
</doc>