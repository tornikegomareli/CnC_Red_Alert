/*
 * template_inst.cpp — Explicit template instantiations
 * The original Watcom build implicitly instantiated these.
 * Modern compilers need explicit instantiation for templates
 * defined in headers but used across translation units.
 */

#include "FUNCTION.H"

// VectorClass instantiations
template class VectorClass<CellClass>;
template class VectorClass<ObjectClass*>;
template class VectorClass<char const*>;
template class VectorClass<char*>;
template class VectorClass<void*>;
template class VectorClass<TriggerClass*>;
template class VectorClass<BaseNodeClass>;
template class VectorClass<RemapControlType*>;
template class VectorClass<FileEntryClass*>;
template class VectorClass<MultiMission*>;
template class VectorClass<NodeNameTag*>;
template class VectorClass<PhoneEntryClass*>;

// DynamicVectorClass instantiations
template class DynamicVectorClass<ObjectClass*>;
template class DynamicVectorClass<TriggerClass*>;
template class DynamicVectorClass<char const*>;
template class DynamicVectorClass<char*>;
template class DynamicVectorClass<void*>;
template class DynamicVectorClass<BaseNodeClass>;
template class DynamicVectorClass<RemapControlType*>;
template class DynamicVectorClass<PhoneEntryClass*>;
template class DynamicVectorClass<FileEntryClass*>;
template class DynamicVectorClass<MultiMission*>;
template class DynamicVectorClass<NodeNameTag*>;
// DynamicVectorClass<EgoClass*> already instantiated in FUNCTION.H

// TFixedIHeapClass instantiations
template class TFixedIHeapClass<AircraftClass>;
template class TFixedIHeapClass<AircraftTypeClass>;
template class TFixedIHeapClass<AnimClass>;
template class TFixedIHeapClass<AnimTypeClass>;
template class TFixedIHeapClass<BuildingClass>;
template class TFixedIHeapClass<BuildingTypeClass>;
template class TFixedIHeapClass<BulletClass>;
template class TFixedIHeapClass<BulletTypeClass>;
template class TFixedIHeapClass<FactoryClass>;
template class TFixedIHeapClass<HouseClass>;
template class TFixedIHeapClass<HouseTypeClass>;
template class TFixedIHeapClass<InfantryClass>;
template class TFixedIHeapClass<InfantryTypeClass>;
template class TFixedIHeapClass<OverlayClass>;
template class TFixedIHeapClass<OverlayTypeClass>;
template class TFixedIHeapClass<SmudgeClass>;
template class TFixedIHeapClass<SmudgeTypeClass>;
template class TFixedIHeapClass<TeamClass>;
template class TFixedIHeapClass<TeamTypeClass>;
template class TFixedIHeapClass<TemplateClass>;
template class TFixedIHeapClass<TemplateTypeClass>;
template class TFixedIHeapClass<TerrainClass>;
template class TFixedIHeapClass<TerrainTypeClass>;
template class TFixedIHeapClass<TriggerClass>;
template class TFixedIHeapClass<TriggerTypeClass>;
template class TFixedIHeapClass<UnitClass>;
template class TFixedIHeapClass<UnitTypeClass>;
template class TFixedIHeapClass<VesselClass>;
template class TFixedIHeapClass<VesselTypeClass>;
template class TFixedIHeapClass<WarheadTypeClass>;
template class TFixedIHeapClass<WeaponTypeClass>;

// CCPtr::Heap static members already defined in CCPTR.CPP

// MixFileClass
template class MixFileClass<CCFileClass>;
