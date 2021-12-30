#include "world_item.hpp"
#include "game_interface.hpp"
#include "item_reference.hpp"

WorldItem::WorldItem(
    std::shared_ptr<ItemReference> ref, std::shared_ptr<jt::DrawableInterface> drawable)
{
    m_refId = ref->referenceId;
    m_drawable = drawable;
    m_drawable->setOffset(ref->worldItemOffset);
}

void WorldItem::doCreate() { }
void WorldItem::doUpdate(float const elapsed) { m_drawable->update(elapsed); }
void WorldItem::doDraw() const { m_drawable->draw(getGame()->gfx().target()); }

std::shared_ptr<jt::DrawableInterface> WorldItem::getDrawable() { return m_drawable; }
std::string WorldItem::getRefId() const { return m_refId; }
