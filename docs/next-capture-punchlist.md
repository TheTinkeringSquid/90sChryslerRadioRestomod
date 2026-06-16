# Round-2 Capture Punch List

Everything still needed to fully unblock the schematic, after the first photo
pass (2026-06-16) resolved OQ-1/3/5/8/13. Work top-down — **Priority 1 (IC
markings) is the real blocker**; the rest can be batched whenever the meter and
calipers are out. Each item notes the target file and the open question it
closes.

Drop new photos in `G:\My Drive\Claude` (same as before) and I'll read + file
them. Measurements can be typed to me or written straight into the linked file.

---

## Priority 1 — Legible IC part numbers  → RE §1
The current main-board/preamp shots are too soft to read chip markings; these
P/Ns drive the tuner, amp, codec, and display-driver choices.

**Shoot list (one sharp, glare-free macro each):**
- [ ] Main board — **microcontroller** (largest SOIC) → RE §1
- [ ] Main board — **tuner** section IC / shielded can markings → RE §1
- [ ] Main board — **`U4` (ST-logo DIP)** — confirm full P/N → RE §1
- [ ] Main board — any other ICs (`U1`, `U2`, regulators near rear header) → RE §1
- [ ] **Amplifier IC** on the chassis heatsink bracket (the big multi-pin power
      device) → RE §1, sizes the new amp
- [ ] Cassette **preamp board** — both DIP ICs (preamp + likely Dolby-B NR) → RE §1
- [ ] Faceplate — **VFD driver IC** near the display → RE §1, OQ-2

**Photo tips for readable markings:**
- Fill the frame with the chip; tap to focus *on the text*, then shoot.
- Kill glare: light raking from the **side**, not straight on; turn off flash.
  Laser-etched marks read best at a shallow angle with diffuse light.
- Hold steady / brace the phone — motion blur is what killed the first set.
- A second shot per IC from a different angle helps if etching is faint.

---

## Priority 2 — Electrical measurements (multimeter)  → RE §3, §4
- [ ] **Pot values + taper** for volume, balance, fader (rotary) and bass, treble
      (slider): end-to-end resistance + wiper at 0/25/50/75/100 % → RE §3, **OQ-6**
- [ ] **Volume power switch**: confirm the click on/off contacts (continuity) → RE §3
- [ ] **Button scheme**: press each S201–S207+ in continuity mode; record which
      pin-pair each closes → confirm matrix vs individual + the map → RE §3, **OQ-4**
- [ ] **Tune control**: is it a pot (smooth resistance) or encoder (A/B toggling,
      detents)? → RE §3, **OQ-7**
- [ ] **VFD filament pins**: find the low-ohm pair on the display's inline row → RE §2, OQ-2
- [ ] **Cassette motor running current** (current-limited ramp at 13.2 V) → RE §4, **OQ-10**
- [ ] **Tape switches**: map tape-present + end-of-tape contacts → RE §4, **OQ-11**

## Priority 3 — Mechanical measurements (calipers)  → mechanical/measurements.md
Pick one datum corner of the main PCB; reference all X,Y to it (mm).
- [ ] Main PCB outline W×D + thickness; mounting-hole X,Y + Ø → **OQ-12**, Edge.Cuts
- [ ] Shaft centers (volume/tune/balance/fader): X,Y + shaft Ø + panel-to-board depth
- [ ] Slider start/end positions + travel (bass, treble)
- [ ] Display window inner W×H + board-to-glass standoff depth
- [ ] Cassette envelope W×H×D + clearance to main board
- [ ] Rear connector + antenna-jack positions/orientation
- [ ] Datum sketch photo → `mechanical/`

## Priority 4 — A few more photos  → archive
- [ ] Main board **bottom / solder side** (full)
- [ ] Faceplate **front straight-on**, filling the frame (faceplate scaling)
- [ ] **VFD pin row** close-up (for pinout mapping)
- [ ] **Rear connectors** straight-on with the Metra 71-1817 mated, if available

---

## When this is done
Resolving Priority 1 + 2 closes OQ-2/4/6/7/9/10/11 and IDs the core ICs;
Priority 3 gives the board outline. At that point the design is fully unblocked
and we proceed: complete electrical design → KiCad schematic → layout → DRC →
gerbers/BOM/CPL = the fab package.
