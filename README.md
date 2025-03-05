# template-mixins by example of a high-performance dynamic_cast substitute

**Author**: Peter Foelsche |
**Date**: October 2024..January 2025 |
**Location**: Austin, TX, USA |
**Email**: [peter_foelsche@outlook.com](mailto:peter_foelsche@outlook.com)

## Introduction

This code avoids calling dynamic_cast<> but relies instead on using virtual functions.
The procedure avoids using virtual base classes, as they cause memory bloat.
