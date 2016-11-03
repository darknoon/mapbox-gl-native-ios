#include <mbgl/renderer/painter.hpp>
#include <mbgl/shader/shaders.hpp>
#include <mbgl/shader/fill_uniforms.hpp>
#include <mbgl/util/clip_id.hpp>

namespace mbgl {

void Painter::renderClippingMask(const UnwrappedTileID& tileID, const ClipID& clip) {
    context.draw({
        gl::DepthMode::disabled(),
        gl::StencilMode {
            gl::StencilMode::Always(),
            static_cast<int32_t>(clip.reference.to_ulong()),
            0b11111111,
            gl::StencilMode::Keep,
            gl::StencilMode::Keep,
            gl::StencilMode::Replace
        },
        gl::ColorMode::disabled(),
        shaders->fill,
        FillColorUniforms::Values {
            uniforms::u_matrix::Value{ matrixForTile(tileID) },
            uniforms::u_opacity::Value{ 0.0f },
            uniforms::u_color::Value{ Color {} },
            uniforms::u_outline_color::Value{ Color {} },
            uniforms::u_world::Value{ context.viewport.getCurrentValue().size },
        },
        gl::Unindexed<gl::Triangles>(tileTriangleVertexBuffer)
    });
}

} // namespace mbgl
