/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_32 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_27 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_32;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_27()
            {
            }
            
            ~RNBOSubpatcher_27()
            {
            }
            
            virtual RNBOSubpatcher_32* getPatcher() const {
                return static_cast<RNBOSubpatcher_32 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                this->dspexpr_01_perform(in1, in2, this->signals[0], n);
                this->dspexpr_02_perform(in1, in2, this->signals[1], n);
                this->selector_01_perform(this->selector_01_onoff, this->signals[0], this->signals[1], out2, n);
                this->signalforwarder_01_perform(out2, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 2; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                RNBO_UNUSED(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void eventinlet_01_out1_bang_bang() {}
            
            void eventinlet_01_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->selector_01_onoff_set(converted);
                }
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 2;
            }
            
            Index getNumOutputChannels() const {
                return 2;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void selector_01_onoff_set(number v) {
                this->selector_01_onoff = v;
            }
            
            void eventinlet_01_out1_number_set(number v) {
                this->selector_01_onoff_set(v);
            }
            
            void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void selector_01_perform(
                number onoff,
                const SampleValue * in1,
                const SampleValue * in2,
                SampleValue * out,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (onoff >= 1 && onoff < 2)
                        out[(Index)i] = in1[(Index)i];
                    else if (onoff >= 2 && onoff < 3)
                        out[(Index)i] = in2[(Index)i];
                    else
                        out[(Index)i] = 0;
                }
            }
            
            void signalforwarder_01_perform(const SampleValue * input, SampleValue * output, Index n) {
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = input[(Index)i];
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                selector_01_onoff = 1;
                dspexpr_01_in1 = 0;
                dspexpr_01_in2 = 0;
                dspexpr_02_in1 = 0;
                dspexpr_02_in2 = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number selector_01_onoff;
                number dspexpr_01_in1;
                number dspexpr_01_in2;
                number dspexpr_02_in1;
                number dspexpr_02_in2;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[2];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_28 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_32;
            friend class rnbomatic;
            
            public:
            
            class RNBOSubpatcher_25 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_28;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_25()
                        {
                        }
                        
                        ~RNBOSubpatcher_25()
                        {
                        }
                        
                        virtual RNBOSubpatcher_28* getPatcher() const {
                            return static_cast<RNBOSubpatcher_28 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
                            getEngine()->flushClockEvents(this, 848255507, false);
                        }
                        
                        MillisecondTime currenttime() {
                            return this->_currentTime;
                        }
                        
                        Index getNumMidiInputPorts() const {
                            return 0;
                        }
                        
                        void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
                        
                        Index getNumMidiOutputPorts() const {
                            return 0;
                        }
                        
                        void process(
                            const SampleValue * const* inputs,
                            Index numInputs,
                            SampleValue * const* outputs,
                            Index numOutputs,
                            Index n
                        ) {
                            RNBO_UNUSED(numOutputs);
                            RNBO_UNUSED(outputs);
                            RNBO_UNUSED(numInputs);
                            RNBO_UNUSED(inputs);
                            this->vs = n;
                            this->updateTime(this->getEngine()->getCurrentTime());
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                                this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                                this->didAllocateSignals = true;
                            }
                        
                            const bool sampleRateChanged = sampleRate != this->sr;
                            const bool maxvsChanged = maxBlockSize != this->maxvs;
                            const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
                        
                            if (sampleRateChanged || maxvsChanged) {
                                this->vs = maxBlockSize;
                                this->maxvs = maxBlockSize;
                                this->sr = sampleRate;
                                this->invsr = 1 / sampleRate;
                            }
                        
                            RNBO_UNUSED(forceDSPSetup);
                        
                            if (sampleRateChanged)
                                this->onSampleRateChanged(sampleRate);
                        }
                        
                        void setProbingTarget(MessageTag id) {
                            switch (id) {
                            default:
                                {
                                this->setProbingIndex(-1);
                                break;
                                }
                            }
                        }
                        
                        void setProbingIndex(ProbingIndex ) {}
                        
                        Index getProbingChannels(MessageTag outletId) const {
                            RNBO_UNUSED(outletId);
                            return 0;
                        }
                        
                        void setVoiceIndex(Index index)  {
                            this->_voiceIndex = index;
                        }
                        
                        void setNoteNumber(Int noteNumber)  {
                            this->_noteNumber = noteNumber;
                        }
                        
                        Index getIsMuted()  {
                            return this->isMuted;
                        }
                        
                        void setIsMuted(Index v)  {
                            this->isMuted = v;
                        }
                        
                        void onSampleRateChanged(double ) {}
                        
                        Index getPatcherSerial() const {
                            return 0;
                        }
                        
                        void getState(PatcherStateInterface& ) {}
                        
                        void setState() {}
                        
                        void getPreset(PatcherStateInterface& ) {}
                        
                        void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
                        
                        void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValue(index, value, time);
                        }
                        
                        void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                            this->setParameterValue(index, this->getParameterValue(index), time);
                        }
                        
                        void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValueNormalized(index, value, time);
                        }
                        
                        ParameterValue getParameterValue(ParameterIndex index)  {
                            switch (index) {
                            default:
                                {
                                return 0;
                                }
                            }
                        }
                        
                        ParameterIndex getNumSignalInParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumSignalOutParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumParameters() const {
                            return 0;
                        }
                        
                        ConstCharPointer getParameterName(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        ConstCharPointer getParameterId(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
                        
                        void sendParameter(ParameterIndex index, bool ignoreValue) {
                            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
                        }
                        
                        void setParameterOffset(ParameterIndex offset) {
                            this->parameterOffset = offset;
                        }
                        
                        ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                            if (steps == 1) {
                                if (normalizedValue > 0) {
                                    normalizedValue = 1.;
                                }
                            } else {
                                ParameterValue oneStep = (number)1. / (steps - 1);
                                ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                                normalizedValue = numberOfSteps * oneStep;
                            }
                        
                            return normalizedValue;
                        }
                        
                        ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        void scheduleParamInit(ParameterIndex index, Index order) {
                            this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
                        }
                        
                        void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                            RNBO_UNUSED(hasValue);
                            this->updateTime(time);
                        
                            switch (index) {
                            case 848255507:
                                {
                                this->line_01_tick_set(value);
                                break;
                                }
                            }
                        }
                        
                        void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
                        
                        void processOutletEvent(
                            EngineLink* sender,
                            OutletIndex index,
                            ParameterValue value,
                            MillisecondTime time
                        ) {
                            this->updateTime(time);
                            this->processOutletAtCurrentTime(sender, index, value);
                        }
                        
                        void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                            this->updateTime(time);
                        
                            switch (tag) {
                            case TAG("valin"):
                                {
                                if (TAG("poly/OscillatorI/BendFreq/number_obj-22") == objectId)
                                    this->numberobj_01_valin_set(payload);
                        
                                break;
                                }
                            case TAG("format"):
                                {
                                if (TAG("poly/OscillatorI/BendFreq/number_obj-22") == objectId)
                                    this->numberobj_01_format_set(payload);
                        
                                break;
                                }
                            }
                        }
                        
                        void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
                        
                        void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
                        
                        MessageTagInfo resolveTag(MessageTag tag) const {
                            switch (tag) {
                            case TAG("valout"):
                                {
                                return "valout";
                                }
                            case TAG("poly/OscillatorI/BendFreq/number_obj-22"):
                                {
                                return "poly/OscillatorI/BendFreq/number_obj-22";
                                }
                            case TAG("setup"):
                                {
                                return "setup";
                                }
                            case TAG("valin"):
                                {
                                return "valin";
                                }
                            case TAG("format"):
                                {
                                return "format";
                                }
                            }
                        
                            return nullptr;
                        }
                        
                        DataRef* getDataRef(DataRefIndex index)  {
                            switch (index) {
                            default:
                                {
                                return nullptr;
                                }
                            }
                        }
                        
                        DataRefIndex getNumDataRefs() const {
                            return 0;
                        }
                        
                        void fillDataRef(DataRefIndex , DataRef& ) {}
                        
                        void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                        }
                        
                        protected:
                        
                        void eventinlet_02_out1_bang_bang() {
                            this->pak_01_in1_bang();
                        }
                        
                        void eventinlet_02_out1_list_set(const list& v) {
                            {
                                if (v->length > 3)
                                    this->pak_01_in4_set(v[3]);
                        
                                if (v->length > 2)
                                    this->pak_01_in3_set(v[2]);
                        
                                if (v->length > 1)
                                    this->pak_01_in2_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->pak_01_in1_set(converted);
                            }
                        }
                        
                        void line_01_tick_set(number v) {
                            this->line_01_output_set(v);
                        
                            if ((bool)(this->line_01_isFinished(v))) {
                                this->line_01_slope = 0;
                                this->line_01_startValue = v;
                                this->line_01_startPendingRamp();
                            } else {
                                this->line_01_scheduleNext();
                            }
                        }
                        
                        void eventinlet_03_out1_bang_bang() {
                            this->pak_01_in2_bang();
                        }
                        
                        void eventinlet_03_out1_list_set(const list& v) {
                            {
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->pak_01_in2_set(converted);
                            }
                        }
                        
                        void numberobj_01_valin_set(number v) {
                            this->numberobj_01_value_set(v);
                        }
                        
                        void numberobj_01_format_set(number v) {
                            this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
                        }
                        
                        void eventinlet_04_out1_bang_bang() {
                            this->pak_01_in3_bang();
                        }
                        
                        void eventinlet_04_out1_list_set(const list& v) {
                            {
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->pak_01_in3_set(converted);
                            }
                        }
                        
                        void eventinlet_05_out1_bang_bang() {
                            this->pak_01_in4_bang();
                        }
                        
                        void eventinlet_05_out1_list_set(const list& v) {
                            {
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->pak_01_in4_set(converted);
                            }
                        }
                        
                        number msToSamps(MillisecondTime ms, number sampleRate) {
                            return ms * sampleRate * 0.001;
                        }
                        
                        MillisecondTime sampsToMs(SampleIndex samps) {
                            return samps * (this->invsr * 1000);
                        }
                        
                        Index getMaxBlockSize() const {
                            return this->maxvs;
                        }
                        
                        number getSampleRate() const {
                            return this->sr;
                        }
                        
                        bool hasFixedVectorSize() const {
                            return false;
                        }
                        
                        Index getNumInputChannels() const {
                            return 0;
                        }
                        
                        Index getNumOutputChannels() const {
                            return 0;
                        }
                        
                        void initializeObjects() {
                            this->numberobj_01_init();
                        }
                        
                        void sendOutlet(OutletIndex index, ParameterValue value) {
                            this->getEngine()->sendOutlet(this, index, value);
                        }
                        
                        void startup() {}
                        
                        void allocateDataRefs() {}
                        
                        number line_01_time_constrain(number v) const {
                            if (v < 0)
                                v = 0;
                        
                            return v;
                        }
                        
                        void line_01_time_set(number v) {
                            v = this->line_01_time_constrain(v);
                            this->line_01_time = v;
                        }
                        
                        void numberobj_01_output_set(number ) {}
                        
                        void numberobj_01_value_set(number v) {
                            this->numberobj_01_value_setter(v);
                            v = this->numberobj_01_value;
                            number localvalue = v;
                        
                            if (this->numberobj_01_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->getEngine()->sendNumMessage(
                                TAG("valout"),
                                TAG("poly/OscillatorI/BendFreq/number_obj-22"),
                                localvalue,
                                this->_currentTime
                            );
                        
                            this->numberobj_01_output_set(localvalue);
                        }
                        
                        void eventoutlet_01_in1_number_set(number v) {
                            this->getPatcher()->updateTime(this->_currentTime);
                            this->getPatcher()->p_01_out1_number_set(v);
                        }
                        
                        void line_01_output_set(number v) {
                            this->line_01_output = v;
                            this->numberobj_01_value_set(v);
                            this->eventoutlet_01_in1_number_set(v);
                        }
                        
                        void line_01_stop_bang() {
                            this->getEngine()->flushClockEvents(this, 848255507, false);;
                            this->line_01_pendingRamps->length = 0;
                            this->line_01_startValue = this->line_01_output;
                            this->line_01_slope = 0;
                            this->line_01__time = 0;
                            this->line_01_time_set(0);
                        }
                        
                        number line_01_grain_constrain(number v) const {
                            if (v < 0)
                                v = 0;
                        
                            return v;
                        }
                        
                        void line_01_grain_set(number v) {
                            v = this->line_01_grain_constrain(v);
                            this->line_01_grain = v;
                        
                            if ((bool)(!(bool)(this->line_01_isFinished(this->line_01_startValue)))) {
                                this->getEngine()->flushClockEvents(this, 848255507, false);;
                                this->line_01_scheduleNext();
                            }
                        }
                        
                        void line_01_end_bang() {}
                        
                        void line_01_target_set(const list& v) {
                            this->line_01_target = jsCreateListCopy(v);
                            this->line_01_pendingRamps->length = 0;
                        
                            if (v->length == 1) {
                                this->line_01__time = this->line_01_time;
                                this->line_01_time_set(0);
                        
                                if ((bool)(this->line_01__time)) {
                                    this->line_01_startRamp(v[0], this->line_01__time);
                                } else {
                                    this->line_01_output_set(v[0]);
                                    this->line_01_startValue = v[0];
                                    this->line_01_stop_bang();
                                }
                            } else if (v->length == 2) {
                                this->line_01_time_set(0);
                                this->line_01__time = (v[1] < 0 ? 0 : v[1]);
                                this->line_01_startRamp(v[0], this->line_01__time);
                            } else if (v->length == 3) {
                                this->line_01_time_set(0);
                                this->line_01_grain_set(v[2]);
                                this->line_01__time = (v[1] < 0 ? 0 : v[1]);
                                this->line_01_startRamp(v[0], this->line_01__time);
                            } else {
                                this->line_01_time_set(0);
                                this->line_01_pendingRamps = jsCreateListCopy(v);
                                this->line_01_startPendingRamp();
                            }
                        }
                        
                        void codebox_01_out2_set(number v) {
                            this->codebox_01_out2 = v;
                        
                            {
                                list converted = {this->codebox_01_out2};
                                this->line_01_target_set(converted);
                            }
                        }
                        
                        void codebox_01_in1_set(const list& in1) {
                            this->codebox_01_in1 = jsCreateListCopy(in1);
                            number x = this->codebox_01_in1[0];
                            number y = this->codebox_01_in1[1];
                            number z = this->codebox_01_in1[2];
                            number bendFactor = this->codebox_01_in1[3];
                        
                            if (bendFactor >= 0) {
                                this->codebox_01_out2_set(y + bendFactor * (z - y));//#map:_###_obj_###_:6
                            } else {
                                this->codebox_01_out2_set(x + -bendFactor * (x - y));//#map:_###_obj_###_:8
                            }//#map:OscillatorI/BendFreq/codebox_obj-12:5
                        }
                        
                        void pak_01_out_set(const list& v) {
                            this->codebox_01_in1_set(v);
                        }
                        
                        void pak_01_in3_set(number v) {
                            this->pak_01_in3 = v;
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_01_in1);
                            array[1] = trunc(this->pak_01_in2);
                            array[2] = trunc(this->pak_01_in3);
                            array[3] = this->pak_01_in4;
                            this->pak_01_out_set(array);
                        }
                        
                        void eventinlet_04_out1_number_set(number v) {
                            this->pak_01_in3_set(v);
                        }
                        
                        void pak_01_in2_set(number v) {
                            this->pak_01_in2 = v;
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_01_in1);
                            array[1] = trunc(this->pak_01_in2);
                            array[2] = trunc(this->pak_01_in3);
                            array[3] = this->pak_01_in4;
                            this->pak_01_out_set(array);
                        }
                        
                        void eventinlet_03_out1_number_set(number v) {
                            this->pak_01_in2_set(v);
                        }
                        
                        void pak_01_in1_set(number v) {
                            this->pak_01_in1 = v;
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_01_in1);
                            array[1] = trunc(this->pak_01_in2);
                            array[2] = trunc(this->pak_01_in3);
                            array[3] = this->pak_01_in4;
                            this->pak_01_out_set(array);
                        }
                        
                        void eventinlet_02_out1_number_set(number v) {
                            this->pak_01_in1_set(v);
                        }
                        
                        void pak_01_in4_set(number v) {
                            this->pak_01_in4 = v;
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_01_in1);
                            array[1] = trunc(this->pak_01_in2);
                            array[2] = trunc(this->pak_01_in3);
                            array[3] = this->pak_01_in4;
                            this->pak_01_out_set(array);
                        }
                        
                        void eventinlet_05_out1_number_set(number v) {
                            this->pak_01_in4_set(v);
                        }
                        
                        void pak_01_in1_bang() {
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_01_in1);
                            array[1] = trunc(this->pak_01_in2);
                            array[2] = trunc(this->pak_01_in3);
                            array[3] = this->pak_01_in4;
                            this->pak_01_out_set(array);
                        }
                        
                        void pak_01_in2_bang() {
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_01_in1);
                            array[1] = trunc(this->pak_01_in2);
                            array[2] = trunc(this->pak_01_in3);
                            array[3] = this->pak_01_in4;
                            this->pak_01_out_set(array);
                        }
                        
                        void pak_01_in3_bang() {
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_01_in1);
                            array[1] = trunc(this->pak_01_in2);
                            array[2] = trunc(this->pak_01_in3);
                            array[3] = this->pak_01_in4;
                            this->pak_01_out_set(array);
                        }
                        
                        void pak_01_in4_bang() {
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_01_in1);
                            array[1] = trunc(this->pak_01_in2);
                            array[2] = trunc(this->pak_01_in3);
                            array[3] = this->pak_01_in4;
                            this->pak_01_out_set(array);
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
                        }
                        
                        void numberobj_01_value_setter(number v) {
                            number localvalue = v;
                        
                            if (this->numberobj_01_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->numberobj_01_value = localvalue;
                        }
                        
                        number line_01_valueAtTime(MillisecondTime time) {
                            return this->line_01_startValue + this->line_01_slope * (time - this->line_01_startTime);
                        }
                        
                        void line_01_scheduleNext() {
                            MillisecondTime currentTime = (MillisecondTime)(this->currenttime());
                            number nextTime = currentTime + this->line_01_grain;
                            number nextValue;
                        
                            if (nextTime - this->line_01_startTime >= this->line_01__time || this->line_01_grain == 0) {
                                nextTime = this->line_01_startTime + this->line_01__time;
                                nextValue = this->line_01_currentTarget;
                            } else {
                                nextValue = this->line_01_valueAtTime(nextTime);
                            }
                        
                            this->getEngine()->scheduleClockEventWithValue(this, 848255507, nextTime - currentTime + this->_currentTime, nextValue);;
                        }
                        
                        void line_01_startRamp(number target, MillisecondTime time) {
                            MillisecondTime currentTime = (MillisecondTime)(this->currenttime());
                            this->line_01_startValue = this->line_01_valueAtTime(currentTime);
                            this->line_01_startTime = currentTime;
                            this->line_01_currentTarget = target;
                            this->getEngine()->flushClockEvents(this, 848255507, false);;
                            number rise = target - this->line_01_startValue;
                            this->line_01_slope = rise / time;
                            this->line_01_scheduleNext();
                        }
                        
                        bool line_01_isFinished(number value) {
                            return value == this->line_01_currentTarget && this->currenttime() - this->line_01_startTime >= this->line_01__time;
                        }
                        
                        void line_01_startPendingRamp() {
                            if (this->line_01_pendingRamps->length < 2) {
                                this->line_01_pendingRamps->length = 0;
                                this->line_01__time = 0;
                                this->line_01_time_set(0);
                                this->line_01_end_bang();
                                return;
                            }
                        
                            if (this->line_01_pendingRamps->length > 1) {
                                number target = this->line_01_pendingRamps->shift();
                                this->line_01__time = this->line_01_pendingRamps->shift();
                                this->line_01__time = (this->line_01__time < 0 ? 0 : this->line_01__time);
                                this->line_01_startRamp(target, this->line_01__time);
                            }
                        }
                        
                        void numberobj_01_init() {
                            this->numberobj_01_currentFormat = 6;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/OscillatorI/BendFreq/number_obj-22"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
                            preset["value"] = this->numberobj_01_value;
                        }
                        
                        void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
                            if ((bool)(stateIsEmpty(preset)))
                                return;
                        
                            this->numberobj_01_value_set(preset["value"]);
                        }
                        
                        bool stackprotect_check() {
                            this->stackprotect_count++;
                        
                            if (this->stackprotect_count > 128) {
                                console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                                return true;
                            }
                        
                            return false;
                        }
                        
                        void updateTime(MillisecondTime time) {
                            this->_currentTime = time;
                            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
                        
                            if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
                        
                            if (this->sampleOffsetIntoNextAudioBuffer < 0)
                                this->sampleOffsetIntoNextAudioBuffer = 0;
                        }
                        
                        void assign_defaults()
                        {
                            line_01_time = 0;
                            line_01_grain = 20;
                            line_01_output = 0;
                            codebox_01_out2 = 0;
                            pak_01_in1 = 0;
                            pak_01_in2 = 0;
                            pak_01_in3 = 0;
                            pak_01_in4 = 0;
                            numberobj_01_value = 0;
                            numberobj_01_value_setter(numberobj_01_value);
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            line_01_startTime = 0;
                            line_01_startValue = 20;
                            line_01_currentTarget = 0;
                            line_01_slope = 0;
                            line_01__time = 0;
                            numberobj_01_currentFormat = 6;
                            numberobj_01_lastValue = 0;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            list line_01_target;
                            number line_01_time;
                            number line_01_grain;
                            number line_01_output;
                            list codebox_01_in1;
                            number codebox_01_out2;
                            number pak_01_in1;
                            number pak_01_in2;
                            number pak_01_in3;
                            number pak_01_in4;
                            number numberobj_01_value;
                            MillisecondTime _currentTime;
                            UInt64 audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            MillisecondTime line_01_startTime;
                            number line_01_startValue;
                            number line_01_currentTarget;
                            number line_01_slope;
                            MillisecondTime line_01__time;
                            list line_01_pendingRamps;
                            Int numberobj_01_currentFormat;
                            number numberobj_01_lastValue;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            RNBOSubpatcher_28()
            {
            }
            
            ~RNBOSubpatcher_28()
            {
                delete this->p_01;
            }
            
            virtual RNBOSubpatcher_32* getPatcher() const {
                return static_cast<RNBOSubpatcher_32 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            number samplerate() const {
                return this->sr;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                this->p_01_perform(n);
            
                this->cycle_tilde_01_perform(
                    this->cycle_tilde_01_frequency,
                    this->cycle_tilde_01_phase_offset,
                    this->signals[0],
                    this->dummyBuffer,
                    n
                );
            
                this->tri_tilde_01_perform(
                    this->tri_tilde_01_frequency,
                    this->tri_tilde_01_pulsewidth,
                    this->tri_tilde_01_syncPhase,
                    this->signals[1],
                    this->dummyBuffer,
                    n
                );
            
                this->rect_tilde_01_perform(
                    this->rect_tilde_01_frequency,
                    this->rect_tilde_01_pulsewidth,
                    this->rect_tilde_01_syncPhase,
                    this->signals[2],
                    this->dummyBuffer,
                    n
                );
            
                this->saw_tilde_01_perform(
                    this->saw_tilde_01_frequency,
                    this->saw_tilde_01_syncPhase,
                    this->signals[3],
                    this->dummyBuffer,
                    n
                );
            
                this->selector_02_perform(
                    this->selector_02_onoff,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    this->signals[3],
                    this->signals[4],
                    n
                );
            
                this->dspexpr_03_perform(this->signals[4], this->dspexpr_03_in2, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 5; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->cycle_tilde_01_dspsetup(forceDSPSetup);
                this->tri_tilde_01_dspsetup(forceDSPSetup);
                this->saw_tilde_01_dspsetup(forceDSPSetup);
                this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
                this->p_01->setVoiceIndex(index);
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
                this->p_01->setNoteNumber(noteNumber);
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {
                this->p_01 = new RNBOSubpatcher_25();
                this->p_01->setEngineAndPatcher(this->getEngine(), this);
                this->p_01->initialize();
                this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
            }
            
            void getPreset(PatcherStateInterface& preset) {
                this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "BendFreq"));
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                RNBO_UNUSED(v);
                this->updateTime(time);
            
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_01->getNumParameters())
                        this->p_01->setParameterValue(index, v, time);
            
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->getParameterValue(index);
            
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0 + this->p_01->getNumParameters();
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->getParameterName(index);
            
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->getParameterId(index);
            
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    default:
                        {
                        index -= 0;
            
                        if (index < this->p_01->getNumParameters())
                            this->p_01->getParameterInfo(index, info);
            
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
                if (subpatcher == this->p_01)
                    return 0;
            
                return 0;
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->convertToNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->convertFromNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->constrainParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("valin"):
                    {
                    if (TAG("poly/OscillatorI/number_obj-24") == objectId)
                        this->numberobj_02_valin_set(payload);
            
                    break;
                    }
                case TAG("format"):
                    {
                    if (TAG("poly/OscillatorI/number_obj-24") == objectId)
                        this->numberobj_02_format_set(payload);
            
                    break;
                    }
                }
            
                this->p_01->processNumMessage(tag, objectId, time, payload);
            }
            
            void processListMessage(
                MessageTag tag,
                MessageTag objectId,
                MillisecondTime time,
                const list& payload
            ) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_01->processListMessage(tag, objectId, time, payload);
            }
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_01->processBangMessage(tag, objectId, time);
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
                case TAG("valout"):
                    {
                    return "valout";
                    }
                case TAG("poly/OscillatorI/number_obj-24"):
                    {
                    return "poly/OscillatorI/number_obj-24";
                    }
                case TAG("setup"):
                    {
                    return "setup";
                    }
                case TAG("valin"):
                    {
                    return "valin";
                    }
                case TAG("format"):
                    {
                    return "format";
                    }
                }
            
                auto subpatchResult_0 = this->p_01->resolveTag(tag);
            
                if (subpatchResult_0)
                    return subpatchResult_0;
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 0) {
                    this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
                    this->cycle_tilde_01_bufferUpdated();
                }
            
                this->p_01->processDataViewUpdate(index, time);
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
                this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
            }
            
            protected:
            
            void eventinlet_06_out1_bang_bang() {}
            
            void eventinlet_06_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->midiparse_01_midiin_set(converted);
                }
            }
            
            void eventinlet_07_out1_bang_bang() {}
            
            void eventinlet_07_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->selector_02_onoff_set(converted);
                }
            }
            
            void eventinlet_08_out1_bang_bang() {
                this->expr_01_in2_bang();
            }
            
            void eventinlet_08_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_01_in2_set(converted);
                }
            }
            
            void eventinlet_09_out1_bang_bang() {}
            
            void eventinlet_09_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->dspexpr_03_in2_set(converted);
                }
            }
            
            void eventinlet_10_out1_bang_bang() {
                this->codebox_04_in2_bang();
                this->codebox_02_in2_bang();
            }
            
            void eventinlet_10_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->codebox_04_in2_set(converted);
                }
            
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->codebox_02_in2_set(converted);
                }
            }
            
            void numberobj_02_valin_set(number v) {
                this->numberobj_02_value_set(v);
            }
            
            void numberobj_02_format_set(number v) {
                this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {
                this->numberobj_02_init();
                this->p_01->initializeObjects();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->p_01->startup();
            }
            
            void allocateDataRefs() {
                this->p_01->allocateDataRefs();
                this->cycle_tilde_01_buffer->requestSize(16384, 1);
                this->cycle_tilde_01_buffer->setSampleRate(this->sr);
                this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
            }
            
            void selector_02_onoff_set(number v) {
                this->selector_02_onoff = v;
            }
            
            void eventinlet_07_out1_number_set(number v) {
                this->selector_02_onoff_set(v);
            }
            
            void expr_01_in2_set(number v) {
                this->expr_01_in2 = v;
            }
            
            void eventinlet_08_out1_number_set(number v) {
                this->expr_01_in2_set(v);
            }
            
            void codebox_04_in2_set(number v) {
                this->codebox_04_in2 = v;
            }
            
            void codebox_02_in2_set(number v) {
                this->codebox_02_in2 = v;
            }
            
            void eventinlet_10_out1_number_set(number v) {
                this->codebox_04_in2_set(v);
                this->codebox_02_in2_set(v);
            }
            
            void dspexpr_03_in2_set(number v) {
                this->dspexpr_03_in2 = v;
            }
            
            void eventinlet_09_out1_number_set(number v) {
                this->dspexpr_03_in2_set(v);
            }
            
            void midiparse_01_channel_set(number ) {}
            
            void unpack_01_out2_set(number v) {
                this->unpack_01_out2 = v;
            }
            
            void saw_tilde_01_frequency_set(number v) {
                this->saw_tilde_01_frequency = v;
            }
            
            void rect_tilde_01_frequency_set(number v) {
                this->rect_tilde_01_frequency = v;
            }
            
            void tri_tilde_01_frequency_set(number v) {
                this->tri_tilde_01_frequency = v;
            }
            
            void cycle_tilde_01_frequency_set(number v) {
                this->cycle_tilde_01_frequency = v;
            }
            
            void p_01_out1_number_set(number v) {
                this->saw_tilde_01_frequency_set(v);
                this->rect_tilde_01_frequency_set(v);
                this->tri_tilde_01_frequency_set(v);
                this->cycle_tilde_01_frequency_set(v);
            }
            
            void p_01_in3_number_set(number v) {
                this->p_01->updateTime(this->_currentTime);
                this->p_01->eventinlet_04_out1_number_set(v);
            }
            
            void codebox_04_out1_set(number v) {
                this->codebox_04_out1 = v;
                this->p_01_in3_number_set(this->codebox_04_out1);
            }
            
            void codebox_04_in1_set(number in1) {
                this->codebox_04_in1 = in1;
            
                list freqs = {
                    16.351625,
                    17.22640329,
                    17.44173333,
                    18.16847222,
                    18.39557813,
                    19.3797037,
                    19.62195,
                    20.43953125,
                    20.69502539,
                    21.80216667,
                    22.07469375,
                    22.99447266,
                    23.28190356,
                    24.5274375,
                    25.83960494,
                    26.1626,
                    27.25270833,
                    27.59336719,
                    29.06955556,
                    29.432925,
                    30.65929688,
                    31.04253809,
                    32.70325,
                    34.45280658,
                    34.88346667,
                    36.33694444,
                    36.79115625,
                    38.75940741,
                    39.2439,
                    40.8790625,
                    41.39005078,
                    43.60433333,
                    44.1493875,
                    45.98894531,
                    46.56380713,
                    49.054875,
                    51.67920988,
                    52.3252,
                    54.50541667,
                    55.18673438,
                    58.13911111,
                    58.86585,
                    61.31859375,
                    62.08507617,
                    65.4065,
                    68.90561317,
                    69.76693333,
                    72.67388889,
                    73.5823125,
                    77.51881481,
                    78.4878,
                    81.758125,
                    82.78010156,
                    87.20866667,
                    88.298775,
                    91.97789063,
                    93.12761426,
                    98.10975,
                    103.3584198,
                    104.6504,
                    109.0108333,
                    110.3734688,
                    116.2782222,
                    117.7317,
                    122.6371875,
                    124.1701523,
                    130.813,
                    137.8112263,
                    139.5338667,
                    145.3477778,
                    147.164625,
                    155.0376296,
                    156.9756,
                    163.51625,
                    165.5602031,
                    174.4173333,
                    176.59755,
                    183.9557813,
                    186.2552285,
                    196.2195,
                    206.7168395,
                    209.3008,
                    218.0216667,
                    220.7469375,
                    232.5564444,
                    235.4634,
                    245.274375,
                    248.3403047,
                    261.626,
                    275.6224527,
                    279.0677333,
                    290.6955556,
                    294.32925,
                    310.0752593,
                    313.9512,
                    327.0325,
                    331.1204063,
                    348.8346667,
                    353.1951,
                    367.9115625,
                    372.510457,
                    392.439,
                    413.433679,
                    418.6016,
                    436.0433333,
                    441.493875,
                    465.1128889,
                    470.9268,
                    490.54875,
                    496.6806094,
                    523.252,
                    551.2449053,
                    558.1354667,
                    581.3911111,
                    588.6585,
                    620.1505185,
                    627.9024,
                    654.065,
                    662.2408125,
                    697.6693333,
                    706.3902,
                    735.823125,
                    745.0209141,
                    784.878,
                    826.867358,
                    837.2032,
                    872.0866667,
                    882.98775,
                    930.2257778,
                    941.8536,
                    981.0975,
                    993.3612188,
                    1046.504,
                    1102.489811,
                    1116.270933,
                    1162.782222,
                    1177.317,
                    1240.301037,
                    1255.8048,
                    1308.13,
                    1324.481625,
                    1395.338667,
                    1412.7804,
                    1471.64625,
                    1490.041828,
                    1569.756,
                    1653.734716,
                    1674.4064,
                    1744.173333,
                    1765.9755,
                    1860.451556,
                    1883.7072,
                    1962.195,
                    1986.722438,
                    2093.008,
                    2204.979621,
                    2232.541867,
                    2325.564444,
                    2354.634,
                    2480.602074,
                    2511.6096,
                    2616.26,
                    2648.96325,
                    2790.677333,
                    2825.5608,
                    2943.2925,
                    2980.083656,
                    3139.512,
                    3307.469432,
                    3348.8128,
                    3488.346667,
                    3531.951,
                    3720.903111,
                    3767.4144,
                    3924.39,
                    3973.444875,
                    4186.016,
                    4409.959243,
                    4465.083733,
                    4651.128889,
                    4709.268,
                    4961.204148,
                    5023.2192,
                    5232.52,
                    5297.9265,
                    5581.354667,
                    5651.1216,
                    5886.585,
                    5960.167313,
                    6279.024,
                    6614.938864,
                    6697.6256,
                    6976.693333,
                    7063.902,
                    7441.806222,
                    7534.8288,
                    7848.78,
                    7946.88975,
                    8372.032,
                    8819.918486,
                    8930.167467,
                    9302.257778,
                    9418.536,
                    9922.408296,
                    10046.4384,
                    10465.04,
                    10595.853,
                    11162.70933,
                    11302.2432,
                    11773.17,
                    11920.33463,
                    12558.048,
                    13229.87773,
                    13395.2512,
                    13953.38667,
                    14127.804,
                    14883.61244,
                    15069.6576,
                    15697.56,
                    15893.7795,
                    16744.064,
                    17639.83697,
                    17860.33493,
                    18604.51556,
                    18837.072,
                    19844.81659,
                    20092.8768,
                    20930.08,
                    21191.706,
                    22325.41867,
                    22604.4864,
                    23546.34,
                    23840.66925,
                    25116.096,
                    26459.75546,
                    26790.5024,
                    27906.77333,
                    28255.608,
                    29767.22489,
                    30139.3152,
                    31395.12,
                    31787.559,
                    33488.128,
                    35279.67394,
                    35720.66987,
                    37209.03111,
                    37674.144,
                    39689.63319,
                    40185.7536,
                    41860.16,
                    42383.412,
                    44650.83733,
                    45208.9728,
                    47092.68,
                    47681.3385,
                    50232.192,
                    52919.51091,
                    53581.0048,
                    55813.54667,
                    56511.216,
                    59534.44978,
                    60278.6304,
                    62790.24,
                    63575.118
                };
            
                number midiNum = this->codebox_04_in1;
                number freq = freqs[(Index)(midiNum + this->codebox_04_in2)];
                this->codebox_04_out1_set(freq);//#map:OscillatorI/codebox_obj-26:4
            }
            
            void p_01_in2_number_set(number v) {
                this->p_01->updateTime(this->_currentTime);
                this->p_01->eventinlet_03_out1_number_set(v);
            }
            
            void codebox_03_out1_set(number v) {
                this->codebox_03_out1 = v;
                this->p_01_in2_number_set(this->codebox_03_out1);
            }
            
            void codebox_03_in1_set(number in1) {
                this->codebox_03_in1 = in1;
            
                list freqs = {
                    16.351625,
                    17.22640329,
                    17.44173333,
                    18.16847222,
                    18.39557813,
                    19.3797037,
                    19.62195,
                    20.43953125,
                    20.69502539,
                    21.80216667,
                    22.07469375,
                    22.99447266,
                    23.28190356,
                    24.5274375,
                    25.83960494,
                    26.1626,
                    27.25270833,
                    27.59336719,
                    29.06955556,
                    29.432925,
                    30.65929688,
                    31.04253809,
                    32.70325,
                    34.45280658,
                    34.88346667,
                    36.33694444,
                    36.79115625,
                    38.75940741,
                    39.2439,
                    40.8790625,
                    41.39005078,
                    43.60433333,
                    44.1493875,
                    45.98894531,
                    46.56380713,
                    49.054875,
                    51.67920988,
                    52.3252,
                    54.50541667,
                    55.18673438,
                    58.13911111,
                    58.86585,
                    61.31859375,
                    62.08507617,
                    65.4065,
                    68.90561317,
                    69.76693333,
                    72.67388889,
                    73.5823125,
                    77.51881481,
                    78.4878,
                    81.758125,
                    82.78010156,
                    87.20866667,
                    88.298775,
                    91.97789063,
                    93.12761426,
                    98.10975,
                    103.3584198,
                    104.6504,
                    109.0108333,
                    110.3734688,
                    116.2782222,
                    117.7317,
                    122.6371875,
                    124.1701523,
                    130.813,
                    137.8112263,
                    139.5338667,
                    145.3477778,
                    147.164625,
                    155.0376296,
                    156.9756,
                    163.51625,
                    165.5602031,
                    174.4173333,
                    176.59755,
                    183.9557813,
                    186.2552285,
                    196.2195,
                    206.7168395,
                    209.3008,
                    218.0216667,
                    220.7469375,
                    232.5564444,
                    235.4634,
                    245.274375,
                    248.3403047,
                    261.626,
                    275.6224527,
                    279.0677333,
                    290.6955556,
                    294.32925,
                    310.0752593,
                    313.9512,
                    327.0325,
                    331.1204063,
                    348.8346667,
                    353.1951,
                    367.9115625,
                    372.510457,
                    392.439,
                    413.433679,
                    418.6016,
                    436.0433333,
                    441.493875,
                    465.1128889,
                    470.9268,
                    490.54875,
                    496.6806094,
                    523.252,
                    551.2449053,
                    558.1354667,
                    581.3911111,
                    588.6585,
                    620.1505185,
                    627.9024,
                    654.065,
                    662.2408125,
                    697.6693333,
                    706.3902,
                    735.823125,
                    745.0209141,
                    784.878,
                    826.867358,
                    837.2032,
                    872.0866667,
                    882.98775,
                    930.2257778,
                    941.8536,
                    981.0975,
                    993.3612188,
                    1046.504,
                    1102.489811,
                    1116.270933,
                    1162.782222,
                    1177.317,
                    1240.301037,
                    1255.8048,
                    1308.13,
                    1324.481625,
                    1395.338667,
                    1412.7804,
                    1471.64625,
                    1490.041828,
                    1569.756,
                    1653.734716,
                    1674.4064,
                    1744.173333,
                    1765.9755,
                    1860.451556,
                    1883.7072,
                    1962.195,
                    1986.722438,
                    2093.008,
                    2204.979621,
                    2232.541867,
                    2325.564444,
                    2354.634,
                    2480.602074,
                    2511.6096,
                    2616.26,
                    2648.96325,
                    2790.677333,
                    2825.5608,
                    2943.2925,
                    2980.083656,
                    3139.512,
                    3307.469432,
                    3348.8128,
                    3488.346667,
                    3531.951,
                    3720.903111,
                    3767.4144,
                    3924.39,
                    3973.444875,
                    4186.016,
                    4409.959243,
                    4465.083733,
                    4651.128889,
                    4709.268,
                    4961.204148,
                    5023.2192,
                    5232.52,
                    5297.9265,
                    5581.354667,
                    5651.1216,
                    5886.585,
                    5960.167313,
                    6279.024,
                    6614.938864,
                    6697.6256,
                    6976.693333,
                    7063.902,
                    7441.806222,
                    7534.8288,
                    7848.78,
                    7946.88975,
                    8372.032,
                    8819.918486,
                    8930.167467,
                    9302.257778,
                    9418.536,
                    9922.408296,
                    10046.4384,
                    10465.04,
                    10595.853,
                    11162.70933,
                    11302.2432,
                    11773.17,
                    11920.33463,
                    12558.048,
                    13229.87773,
                    13395.2512,
                    13953.38667,
                    14127.804,
                    14883.61244,
                    15069.6576,
                    15697.56,
                    15893.7795,
                    16744.064,
                    17639.83697,
                    17860.33493,
                    18604.51556,
                    18837.072,
                    19844.81659,
                    20092.8768,
                    20930.08,
                    21191.706,
                    22325.41867,
                    22604.4864,
                    23546.34,
                    23840.66925,
                    25116.096,
                    26459.75546,
                    26790.5024,
                    27906.77333,
                    28255.608,
                    29767.22489,
                    30139.3152,
                    31395.12,
                    31787.559,
                    33488.128,
                    35279.67394,
                    35720.66987,
                    37209.03111,
                    37674.144,
                    39689.63319,
                    40185.7536,
                    41860.16,
                    42383.412,
                    44650.83733,
                    45208.9728,
                    47092.68,
                    47681.3385,
                    50232.192,
                    52919.51091,
                    53581.0048,
                    55813.54667,
                    56511.216,
                    59534.44978,
                    60278.6304,
                    62790.24,
                    63575.118
                };
            
                number midiNum = this->codebox_03_in1;
                number freq = freqs[(Index)midiNum];
                this->codebox_03_out1_set(freq);//#map:OscillatorI/codebox_obj-25:4
            }
            
            void p_01_in1_number_set(number v) {
                this->p_01->updateTime(this->_currentTime);
                this->p_01->eventinlet_02_out1_number_set(v);
            }
            
            void codebox_02_out1_set(number v) {
                this->codebox_02_out1 = v;
                this->p_01_in1_number_set(this->codebox_02_out1);
            }
            
            void codebox_02_in1_set(number in1) {
                this->codebox_02_in1 = in1;
            
                list freqs = {
                    16.351625,
                    17.22640329,
                    17.44173333,
                    18.16847222,
                    18.39557813,
                    19.3797037,
                    19.62195,
                    20.43953125,
                    20.69502539,
                    21.80216667,
                    22.07469375,
                    22.99447266,
                    23.28190356,
                    24.5274375,
                    25.83960494,
                    26.1626,
                    27.25270833,
                    27.59336719,
                    29.06955556,
                    29.432925,
                    30.65929688,
                    31.04253809,
                    32.70325,
                    34.45280658,
                    34.88346667,
                    36.33694444,
                    36.79115625,
                    38.75940741,
                    39.2439,
                    40.8790625,
                    41.39005078,
                    43.60433333,
                    44.1493875,
                    45.98894531,
                    46.56380713,
                    49.054875,
                    51.67920988,
                    52.3252,
                    54.50541667,
                    55.18673438,
                    58.13911111,
                    58.86585,
                    61.31859375,
                    62.08507617,
                    65.4065,
                    68.90561317,
                    69.76693333,
                    72.67388889,
                    73.5823125,
                    77.51881481,
                    78.4878,
                    81.758125,
                    82.78010156,
                    87.20866667,
                    88.298775,
                    91.97789063,
                    93.12761426,
                    98.10975,
                    103.3584198,
                    104.6504,
                    109.0108333,
                    110.3734688,
                    116.2782222,
                    117.7317,
                    122.6371875,
                    124.1701523,
                    130.813,
                    137.8112263,
                    139.5338667,
                    145.3477778,
                    147.164625,
                    155.0376296,
                    156.9756,
                    163.51625,
                    165.5602031,
                    174.4173333,
                    176.59755,
                    183.9557813,
                    186.2552285,
                    196.2195,
                    206.7168395,
                    209.3008,
                    218.0216667,
                    220.7469375,
                    232.5564444,
                    235.4634,
                    245.274375,
                    248.3403047,
                    261.626,
                    275.6224527,
                    279.0677333,
                    290.6955556,
                    294.32925,
                    310.0752593,
                    313.9512,
                    327.0325,
                    331.1204063,
                    348.8346667,
                    353.1951,
                    367.9115625,
                    372.510457,
                    392.439,
                    413.433679,
                    418.6016,
                    436.0433333,
                    441.493875,
                    465.1128889,
                    470.9268,
                    490.54875,
                    496.6806094,
                    523.252,
                    551.2449053,
                    558.1354667,
                    581.3911111,
                    588.6585,
                    620.1505185,
                    627.9024,
                    654.065,
                    662.2408125,
                    697.6693333,
                    706.3902,
                    735.823125,
                    745.0209141,
                    784.878,
                    826.867358,
                    837.2032,
                    872.0866667,
                    882.98775,
                    930.2257778,
                    941.8536,
                    981.0975,
                    993.3612188,
                    1046.504,
                    1102.489811,
                    1116.270933,
                    1162.782222,
                    1177.317,
                    1240.301037,
                    1255.8048,
                    1308.13,
                    1324.481625,
                    1395.338667,
                    1412.7804,
                    1471.64625,
                    1490.041828,
                    1569.756,
                    1653.734716,
                    1674.4064,
                    1744.173333,
                    1765.9755,
                    1860.451556,
                    1883.7072,
                    1962.195,
                    1986.722438,
                    2093.008,
                    2204.979621,
                    2232.541867,
                    2325.564444,
                    2354.634,
                    2480.602074,
                    2511.6096,
                    2616.26,
                    2648.96325,
                    2790.677333,
                    2825.5608,
                    2943.2925,
                    2980.083656,
                    3139.512,
                    3307.469432,
                    3348.8128,
                    3488.346667,
                    3531.951,
                    3720.903111,
                    3767.4144,
                    3924.39,
                    3973.444875,
                    4186.016,
                    4409.959243,
                    4465.083733,
                    4651.128889,
                    4709.268,
                    4961.204148,
                    5023.2192,
                    5232.52,
                    5297.9265,
                    5581.354667,
                    5651.1216,
                    5886.585,
                    5960.167313,
                    6279.024,
                    6614.938864,
                    6697.6256,
                    6976.693333,
                    7063.902,
                    7441.806222,
                    7534.8288,
                    7848.78,
                    7946.88975,
                    8372.032,
                    8819.918486,
                    8930.167467,
                    9302.257778,
                    9418.536,
                    9922.408296,
                    10046.4384,
                    10465.04,
                    10595.853,
                    11162.70933,
                    11302.2432,
                    11773.17,
                    11920.33463,
                    12558.048,
                    13229.87773,
                    13395.2512,
                    13953.38667,
                    14127.804,
                    14883.61244,
                    15069.6576,
                    15697.56,
                    15893.7795,
                    16744.064,
                    17639.83697,
                    17860.33493,
                    18604.51556,
                    18837.072,
                    19844.81659,
                    20092.8768,
                    20930.08,
                    21191.706,
                    22325.41867,
                    22604.4864,
                    23546.34,
                    23840.66925,
                    25116.096,
                    26459.75546,
                    26790.5024,
                    27906.77333,
                    28255.608,
                    29767.22489,
                    30139.3152,
                    31395.12,
                    31787.559,
                    33488.128,
                    35279.67394,
                    35720.66987,
                    37209.03111,
                    37674.144,
                    39689.63319,
                    40185.7536,
                    41860.16,
                    42383.412,
                    44650.83733,
                    45208.9728,
                    47092.68,
                    47681.3385,
                    50232.192,
                    52919.51091,
                    53581.0048,
                    55813.54667,
                    56511.216,
                    59534.44978,
                    60278.6304,
                    62790.24,
                    63575.118
                };
            
                number midiNum = this->codebox_02_in1;
                number freq = freqs[(Index)(midiNum - this->codebox_02_in2)];
                this->codebox_02_out1_set(freq);//#map:OscillatorI/codebox_obj-9:4
            }
            
            void expr_01_out1_set(number v) {
                this->expr_01_out1 = v;
                this->codebox_04_in1_set(this->expr_01_out1);
                this->codebox_03_in1_set(this->expr_01_out1);
                this->codebox_02_in1_set(this->expr_01_out1);
            }
            
            void expr_01_in1_set(number in1) {
                this->expr_01_in1 = in1;
                this->expr_01_out1_set(this->expr_01_in1 + this->expr_01_in2);//#map:OscillatorI/+_obj-10:1
            }
            
            void unpack_01_out1_set(number v) {
                this->unpack_01_out1 = v;
                this->expr_01_in1_set(v);
            }
            
            void unpack_01_input_list_set(const list& v) {
                if (v->length > 1)
                    this->unpack_01_out2_set(trunc(v[1]));
            
                if (v->length > 0)
                    this->unpack_01_out1_set(trunc(v[0]));
            }
            
            void midiparse_01_noteonoroff_set(const list& v) {
                this->unpack_01_input_list_set(v);
            }
            
            void midiparse_01_polypressure_set(const list& ) {}
            
            void midiparse_01_controlchange_set(const list& ) {}
            
            void midiparse_01_programchange_set(number ) {}
            
            void midiparse_01_aftertouch_set(number ) {}
            
            void p_01_in4_number_set(number v) {
                this->p_01->updateTime(this->_currentTime);
                this->p_01->eventinlet_05_out1_number_set(v);
            }
            
            void numberobj_02_output_set(number v) {
                this->p_01_in4_number_set(v);
            }
            
            void numberobj_02_value_set(number v) {
                this->numberobj_02_value_setter(v);
                v = this->numberobj_02_value;
                number localvalue = v;
            
                if (this->numberobj_02_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("poly/OscillatorI/number_obj-24"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_02_output_set(localvalue);
            }
            
            void midiparse_01_pitchbend_set(number v) {
                this->numberobj_02_value_set(v);
            }
            
            void midiparse_01_midiin_set(number midivalue) {
                list result = this->midiparse_01_parser_next(midivalue);
            
                switch ((int)result[0]) {
                case 0:
                    {
                    this->midiparse_01_channel_set(result[3]);
                    this->midiparse_01_noteonoroff_set({result[1], result[2]});
                    break;
                    }
                case 1:
                    {
                    this->midiparse_01_channel_set(result[3]);
                    this->midiparse_01_polypressure_set({result[1], result[2]});
                    break;
                    }
                case 2:
                    {
                    this->midiparse_01_channel_set(result[3]);
                    this->midiparse_01_controlchange_set({result[1], result[2]});
                    break;
                    }
                case 3:
                    {
                    this->midiparse_01_channel_set(result[2]);
                    this->midiparse_01_programchange_set(result[1]);
                    break;
                    }
                case 4:
                    {
                    this->midiparse_01_channel_set(result[2]);
                    this->midiparse_01_aftertouch_set(result[1]);
                    break;
                    }
                case 5:
                    {
                    this->midiparse_01_channel_set(result[2]);
                    this->midiparse_01_pitchbend_set(result[1]);
                    break;
                    }
                }
            }
            
            void eventinlet_06_out1_number_set(number v) {
                this->midiparse_01_midiin_set(v);
            }
            
            void expr_01_in2_bang() {}
            
            void codebox_04_in2_bang() {}
            
            void codebox_02_in2_bang() {}
            
            void p_01_perform(Index n) {
                // subpatcher: BendFreq
                this->p_01->process(nullptr, 0, nullptr, 0, n);
            }
            
            void cycle_tilde_01_perform(
                number frequency,
                number phase_offset,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(phase_offset);
                auto __cycle_tilde_01_f2i = this->cycle_tilde_01_f2i;
                auto __cycle_tilde_01_buffer = this->cycle_tilde_01_buffer;
                auto __cycle_tilde_01_phasei = this->cycle_tilde_01_phasei;
                Index i;
            
                for (i = 0; i < n; i++) {
                    {
                        uint32_t uint_phase;
            
                        {
                            {
                                uint_phase = __cycle_tilde_01_phasei;
                            }
                        }
            
                        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
                        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                        number y0 = __cycle_tilde_01_buffer[(Index)idx];
                        number y1 = __cycle_tilde_01_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                        number y = y0 + frac * (y1 - y0);
            
                        {
                            uint32_t pincr = (uint32_t)(uint32_trunc(frequency * __cycle_tilde_01_f2i));
                            __cycle_tilde_01_phasei = uint32_add(__cycle_tilde_01_phasei, pincr);
                        }
            
                        out1[(Index)i] = y;
                        out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                        continue;
                    }
                }
            
                this->cycle_tilde_01_phasei = __cycle_tilde_01_phasei;
            }
            
            void tri_tilde_01_perform(
                number frequency,
                number pulsewidth,
                number syncPhase,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(syncPhase);
                RNBO_UNUSED(pulsewidth);
                auto __tri_tilde_01_yn3 = this->tri_tilde_01_yn3;
                auto __tri_tilde_01_yn2 = this->tri_tilde_01_yn2;
                auto __tri_tilde_01_yn1 = this->tri_tilde_01_yn1;
                auto __tri_tilde_01_app_correction = this->tri_tilde_01_app_correction;
                auto __tri_tilde_01_flg = this->tri_tilde_01_flg;
                auto __tri_tilde_01_yn = this->tri_tilde_01_yn;
                auto __tri_tilde_01_t = this->tri_tilde_01_t;
                auto __tri_tilde_01_lastSyncDiff = this->tri_tilde_01_lastSyncDiff;
                auto __tri_tilde_01_lastSyncPhase = this->tri_tilde_01_lastSyncPhase;
                Index i;
            
                for (i = 0; i < n; i++) {
                    number __frequency = frequency;
                    __frequency = rnbo_abs(__frequency);
                    number dt = __frequency / this->samplerate();
            
                    if (dt != 0.0) {
                        number pw = 0.5;
                        {}
                        number syncDiff = 0 - __tri_tilde_01_lastSyncPhase;
                        __tri_tilde_01_lastSyncPhase = 0;
                        __tri_tilde_01_lastSyncDiff = syncDiff;
                        number syncLookahead = 0 + syncDiff;
            
                        if (syncLookahead > 1) {
                            __tri_tilde_01_t = 0;
                        }
            
                        number tCurr = __tri_tilde_01_t;
                        number upSlope = __frequency / (pw * this->samplerate());
                        number downSlope = __frequency / ((1 - pw) * this->samplerate());
            
                        if (tCurr <= pw) {
                            __tri_tilde_01_yn = (number)2 / pw * tCurr - 1;
            
                            if (__tri_tilde_01_flg == -1) {
                                __tri_tilde_01_app_correction = 1;
                                __tri_tilde_01_flg = 1;
                            } else if (__tri_tilde_01_app_correction == 1) {
                                __tri_tilde_01_app_correction = 0;
                                number d = (tCurr - dt) / dt;
                                number d2 = d * d;
                                number d3 = d2 * d;
                                number d4 = d2 * d2;
                                number d5 = d * d4;
                                number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                number h3 = d5 / (number)120;
                                __tri_tilde_01_yn += upSlope * h0;
                                __tri_tilde_01_yn1 += upSlope * h1;
                                __tri_tilde_01_yn2 += upSlope * h2;
                                __tri_tilde_01_yn3 += upSlope * h3;
                            }
            
                            __tri_tilde_01_flg = 1;
                        } else {
                            __tri_tilde_01_yn = 1 - 2 * (tCurr - pw) / (1 - pw);
            
                            if (__tri_tilde_01_flg == 1) {
                                __tri_tilde_01_app_correction = 1;
                            } else if (__tri_tilde_01_app_correction == 1) {
                                __tri_tilde_01_app_correction = 0;
                                number d = (tCurr - pw - dt) / dt;
                                number d2 = d * d;
                                number d3 = d2 * d;
                                number d4 = d2 * d2;
                                number d5 = d4 * d;
                                number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                number h3 = d5 / (number)120;
                                __tri_tilde_01_yn -= downSlope * h0;
                                __tri_tilde_01_yn1 -= downSlope * h1;
                                __tri_tilde_01_yn2 -= downSlope * h2;
                                __tri_tilde_01_yn3 -= downSlope * h3;
                            }
            
                            __tri_tilde_01_flg = -1;
                        }
                    }
            
                    number y = __tri_tilde_01_yn3;
                    __tri_tilde_01_yn3 = __tri_tilde_01_yn2;
                    __tri_tilde_01_yn2 = __tri_tilde_01_yn1;
                    __tri_tilde_01_yn1 = __tri_tilde_01_yn;
                    __tri_tilde_01_t += dt;
            
                    if (dt > 0) {
                        while (__tri_tilde_01_t >= 1) {
                            __tri_tilde_01_t -= 1;
                        }
                    } else {
                        while (__tri_tilde_01_t <= 0) {
                            __tri_tilde_01_t += 1;
                        }
                    }
            
                    y = this->tri_tilde_01_dcblocker_next(y, 0.9997);
                    out1[(Index)i] = y * 0.5;
                    out2[(Index)i] = __tri_tilde_01_t;
                }
            
                this->tri_tilde_01_lastSyncPhase = __tri_tilde_01_lastSyncPhase;
                this->tri_tilde_01_lastSyncDiff = __tri_tilde_01_lastSyncDiff;
                this->tri_tilde_01_t = __tri_tilde_01_t;
                this->tri_tilde_01_yn = __tri_tilde_01_yn;
                this->tri_tilde_01_flg = __tri_tilde_01_flg;
                this->tri_tilde_01_app_correction = __tri_tilde_01_app_correction;
                this->tri_tilde_01_yn1 = __tri_tilde_01_yn1;
                this->tri_tilde_01_yn2 = __tri_tilde_01_yn2;
                this->tri_tilde_01_yn3 = __tri_tilde_01_yn3;
            }
            
            void rect_tilde_01_perform(
                number frequency,
                number pulsewidth,
                number syncPhase,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(syncPhase);
                RNBO_UNUSED(pulsewidth);
                auto __rect_tilde_01_xHistory = this->rect_tilde_01_xHistory;
                auto __rect_tilde_01_yHistory = this->rect_tilde_01_yHistory;
                auto __rect_tilde_01_didSync = this->rect_tilde_01_didSync;
                auto __rect_tilde_01_t = this->rect_tilde_01_t;
                auto __rect_tilde_01_lastSyncDiff = this->rect_tilde_01_lastSyncDiff;
                auto __rect_tilde_01_lastSyncPhase = this->rect_tilde_01_lastSyncPhase;
                Index i;
            
                for (i = 0; i < n; i++) {
                    number __frequency = frequency;
                    __frequency = rnbo_abs(__frequency);
                    number dt = __frequency / this->samplerate();
                    number pw = 0.5;
                    number syncDiff = 0 - __rect_tilde_01_lastSyncPhase;
                    __rect_tilde_01_lastSyncPhase = 0;
                    __rect_tilde_01_lastSyncDiff = syncDiff;
                    number syncLookahead = 0 + syncDiff;
                    number tCurr = __rect_tilde_01_t;
                    number tPrev = tCurr - dt;
                    number tNext = tCurr + dt;
            
                    if (tPrev < 0) {
                        while (tPrev < 0) {
                            tPrev += 1;
                        }
                    }
            
                    if (tNext > 1) {
                        while (tNext >= 1) {
                            tNext -= 1;
                        }
                    }
            
                    number yNext = this->rect_tilde_01_rectangle(tNext, pw);
                    number yCurr = this->rect_tilde_01_rectangle(tCurr, pw);
                    number yPrev = this->rect_tilde_01_rectangle(tPrev, pw);
            
                    if (dt != 0.0) {
                        if (yPrev < yCurr) {
                            number d = tCurr / dt;
                            yCurr += d - 0.5 * d * d - 0.5;
                        } else if (yCurr < yNext) {
                            number d = (1 - tCurr) / dt;
                            yCurr += 0.5 * d * d + d + 0.5;
                        } else if (yPrev > yCurr) {
                            number d = (tCurr - pw) / dt;
                            yCurr -= d - 0.5 * d * d - 0.5;
                        } else if (yCurr > yNext) {
                            number d = (pw - tCurr) / dt;
                            yCurr -= 0.5 * d * d + d + 0.5;
                        } else if ((bool)(__rect_tilde_01_didSync)) {
                            yCurr = 0.25;
                            __rect_tilde_01_didSync = false;
                        } else if (syncLookahead > 1) {
                            if (yCurr < 0) {
                                yCurr = -0.125;
                            }
            
                            __rect_tilde_01_t = 0;
                            __rect_tilde_01_didSync = true;
                        }
            
                        __rect_tilde_01_t += dt;
            
                        if (dt > 0) {
                            while (__rect_tilde_01_t >= 1) {
                                __rect_tilde_01_t -= 1;
                            }
                        } else {
                            while (__rect_tilde_01_t <= 0) {
                                __rect_tilde_01_t += 1;
                            }
                        }
                    }
            
                    number output = yCurr - __rect_tilde_01_yHistory + __rect_tilde_01_xHistory * 0.9997;
                    __rect_tilde_01_xHistory = output;
                    __rect_tilde_01_yHistory = yCurr;
                    out1[(Index)i] = 0.5 * output;
                    out2[(Index)i] = __rect_tilde_01_t;
                }
            
                this->rect_tilde_01_lastSyncPhase = __rect_tilde_01_lastSyncPhase;
                this->rect_tilde_01_lastSyncDiff = __rect_tilde_01_lastSyncDiff;
                this->rect_tilde_01_t = __rect_tilde_01_t;
                this->rect_tilde_01_didSync = __rect_tilde_01_didSync;
                this->rect_tilde_01_yHistory = __rect_tilde_01_yHistory;
                this->rect_tilde_01_xHistory = __rect_tilde_01_xHistory;
            }
            
            void saw_tilde_01_perform(
                number frequency,
                number syncPhase,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(syncPhase);
                auto __saw_tilde_01_didSync = this->saw_tilde_01_didSync;
                auto __saw_tilde_01_lastSyncDiff = this->saw_tilde_01_lastSyncDiff;
                auto __saw_tilde_01_lastSyncPhase = this->saw_tilde_01_lastSyncPhase;
                auto __saw_tilde_01_t = this->saw_tilde_01_t;
                Index i;
            
                for (i = 0; i < n; i++) {
                    number dt = frequency / this->samplerate();
                    number t1 = __saw_tilde_01_t + 0.5;
                    t1 -= trunc(t1);
                    number y = 2 * t1 - 1;
            
                    if (dt != 0.0) {
                        number syncDiff = 0 - __saw_tilde_01_lastSyncPhase;
                        __saw_tilde_01_lastSyncPhase = 0;
                        __saw_tilde_01_lastSyncDiff = syncDiff;
                        number lookahead = 0 + syncDiff;
            
                        if (t1 < dt) {
                            number d = t1 / dt;
                            y -= d + d - d * d - 1;
                        } else if (t1 + dt > 1) {
                            number d = (t1 - 1) / dt;
                            y -= d + d + d * d + 1;
                        } else if ((bool)(__saw_tilde_01_didSync)) {
                            y = 0;
                            __saw_tilde_01_didSync = false;
                        } else if (lookahead > 1) {
                            y *= 0.5;
                            __saw_tilde_01_t = 0;
                            __saw_tilde_01_didSync = true;
                        }
            
                        __saw_tilde_01_t += dt;
            
                        if (dt > 0) {
                            while (__saw_tilde_01_t >= 1) {
                                __saw_tilde_01_t -= 1;
                            }
                        } else {
                            while (__saw_tilde_01_t <= 0) {
                                __saw_tilde_01_t += 1;
                            }
                        }
                    }
            
                    y = this->saw_tilde_01_dcblocker_next(y, 0.9997);
                    out1[(Index)i] = 0.5 * y;
                    out2[(Index)i] = __saw_tilde_01_t;
                }
            
                this->saw_tilde_01_t = __saw_tilde_01_t;
                this->saw_tilde_01_lastSyncPhase = __saw_tilde_01_lastSyncPhase;
                this->saw_tilde_01_lastSyncDiff = __saw_tilde_01_lastSyncDiff;
                this->saw_tilde_01_didSync = __saw_tilde_01_didSync;
            }
            
            void selector_02_perform(
                number onoff,
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                const SampleValue * in4,
                SampleValue * out,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (onoff >= 1 && onoff < 2)
                        out[(Index)i] = in1[(Index)i];
                    else if (onoff >= 2 && onoff < 3)
                        out[(Index)i] = in2[(Index)i];
                    else if (onoff >= 3 && onoff < 4)
                        out[(Index)i] = in3[(Index)i];
                    else if (onoff >= 4 && onoff < 5)
                        out[(Index)i] = in4[(Index)i];
                    else
                        out[(Index)i] = 0;
                }
            }
            
            void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void numberobj_02_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_02_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_02_value = localvalue;
            }
            
            number cycle_tilde_01_ph_next(number freq, number reset) {
                {
                    {
                        if (reset >= 0.)
                            this->cycle_tilde_01_ph_currentPhase = reset;
                    }
                }
            
                number pincr = freq * this->cycle_tilde_01_ph_conv;
            
                if (this->cycle_tilde_01_ph_currentPhase < 0.)
                    this->cycle_tilde_01_ph_currentPhase = 1. + this->cycle_tilde_01_ph_currentPhase;
            
                if (this->cycle_tilde_01_ph_currentPhase > 1.)
                    this->cycle_tilde_01_ph_currentPhase = this->cycle_tilde_01_ph_currentPhase - 1.;
            
                number tmp = this->cycle_tilde_01_ph_currentPhase;
                this->cycle_tilde_01_ph_currentPhase += pincr;
                return tmp;
            }
            
            void cycle_tilde_01_ph_reset() {
                this->cycle_tilde_01_ph_currentPhase = 0;
            }
            
            void cycle_tilde_01_ph_dspsetup() {
                this->cycle_tilde_01_ph_conv = (number)1 / this->sr;
            }
            
            void cycle_tilde_01_dspsetup(bool force) {
                if ((bool)(this->cycle_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->cycle_tilde_01_phasei = 0;
                this->cycle_tilde_01_f2i = (number)4294967296 / this->samplerate();
                this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
                this->cycle_tilde_01_setupDone = true;
                this->cycle_tilde_01_ph_dspsetup();
            }
            
            void cycle_tilde_01_bufferUpdated() {
                this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
            }
            
            list midiparse_01_parser_next(number midiin) {
                int midivalue = (int)(trunc(midiin));
                list result = list(-1);
                number resetByte1 = false;
            
                if (midivalue > 127) {
                    this->midiparse_01_parser_status = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0xFF);
                    this->midiparse_01_parser_byte1 = -1;
                } else {
                    switch ((int)((BinOpInt)this->midiparse_01_parser_status & (BinOpInt)0xF0)) {
                    case 0xB0:
                        {
                        if (this->midiparse_01_parser_byte1 == -1) {
                            this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                2,
                                this->midiparse_01_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_01_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xA0:
                        {
                        if (this->midiparse_01_parser_byte1 == -1) {
                            this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                1,
                                this->midiparse_01_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_01_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xE0:
                        {
                        if (this->midiparse_01_parser_byte1 == -1) {
                            this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            number pitchbend;
            
                            {
                                number val = this->midiparse_01_parser_byte1 + ((BinOpInt)(((BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32)));
            
                                {
                                    val -= 0x2000;
                                    pitchbend = val / (number)8192;
                                }
                            }
            
                            result = {
                                5,
                                pitchbend,
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_01_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xD0:
                        {
                        result = {
                            4,
                            (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                            (BinOpInt)((BinOpInt)(1 + this->midiparse_01_parser_status) & (BinOpInt)0x0F)
                        };
            
                        break;
                        }
                    case 0x90:
                        {
                        if (this->midiparse_01_parser_byte1 == -1) {
                            this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                0,
                                this->midiparse_01_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_01_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xC0:
                        {
                        result = {
                            3,
                            (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                            (BinOpInt)((BinOpInt)(1 + this->midiparse_01_parser_status) & (BinOpInt)0x0F)
                        };
            
                        break;
                        }
                    case 0x80:
                        {
                        if (this->midiparse_01_parser_byte1 == -1) {
                            this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                0,
                                this->midiparse_01_parser_byte1,
                                0,
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_01_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    default:
                        {
                        result = {-1};
                        }
                    }
                }
            
                if (result->length > 1) {
                    result->push(this->midiparse_01_parser_status);
                    result->push(this->midiparse_01_parser_byte1);
                    result->push(midivalue);
                }
            
                if ((bool)(resetByte1)) {
                    this->midiparse_01_parser_byte1 = -1;
                }
            
                return result;
            }
            
            void midiparse_01_parser_reset() {
                this->midiparse_01_parser_status = -1;
                this->midiparse_01_parser_byte1 = -1;
            }
            
            number tri_tilde_01_dcblocker_next(number x, number gain) {
                number y = x - this->tri_tilde_01_dcblocker_xm1 + this->tri_tilde_01_dcblocker_ym1 * gain;
                this->tri_tilde_01_dcblocker_xm1 = x;
                this->tri_tilde_01_dcblocker_ym1 = y;
                return y;
            }
            
            void tri_tilde_01_dcblocker_reset() {
                this->tri_tilde_01_dcblocker_xm1 = 0;
                this->tri_tilde_01_dcblocker_ym1 = 0;
            }
            
            void tri_tilde_01_dcblocker_dspsetup() {
                this->tri_tilde_01_dcblocker_reset();
            }
            
            void tri_tilde_01_dspsetup(bool force) {
                if ((bool)(this->tri_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->tri_tilde_01_setupDone = true;
                this->tri_tilde_01_dcblocker_dspsetup();
            }
            
            number rect_tilde_01_rectangle(number phase, number pulsewidth) {
                if (phase < pulsewidth) {
                    return 1;
                } else {
                    return -1;
                }
            }
            
            number saw_tilde_01_dcblocker_next(number x, number gain) {
                number y = x - this->saw_tilde_01_dcblocker_xm1 + this->saw_tilde_01_dcblocker_ym1 * gain;
                this->saw_tilde_01_dcblocker_xm1 = x;
                this->saw_tilde_01_dcblocker_ym1 = y;
                return y;
            }
            
            void saw_tilde_01_dcblocker_reset() {
                this->saw_tilde_01_dcblocker_xm1 = 0;
                this->saw_tilde_01_dcblocker_ym1 = 0;
            }
            
            void saw_tilde_01_dcblocker_dspsetup() {
                this->saw_tilde_01_dcblocker_reset();
            }
            
            void saw_tilde_01_dspsetup(bool force) {
                if ((bool)(this->saw_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->saw_tilde_01_setupDone = true;
                this->saw_tilde_01_dcblocker_dspsetup();
            }
            
            void numberobj_02_init() {
                this->numberobj_02_currentFormat = 6;
                this->getEngine()->sendNumMessage(TAG("setup"), TAG("poly/OscillatorI/number_obj-24"), 1, this->_currentTime);
            }
            
            void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_02_value;
            }
            
            void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_02_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                dspexpr_03_in1 = 0;
                dspexpr_03_in2 = 0;
                p_01_target = 0;
                selector_02_onoff = 1;
                cycle_tilde_01_frequency = 0;
                cycle_tilde_01_phase_offset = 0;
                expr_01_in1 = 0;
                expr_01_in2 = 0;
                expr_01_out1 = 0;
                codebox_02_in1 = 0;
                codebox_02_in2 = 0;
                codebox_02_out1 = 0;
                unpack_01_out1 = 0;
                unpack_01_out2 = 0;
                tri_tilde_01_frequency = 0;
                tri_tilde_01_pulsewidth = 0.5;
                tri_tilde_01_syncPhase = 0;
                rect_tilde_01_frequency = 0;
                rect_tilde_01_pulsewidth = 0.5;
                rect_tilde_01_syncPhase = 0;
                saw_tilde_01_frequency = 0;
                saw_tilde_01_syncPhase = 0;
                codebox_03_in1 = 0;
                codebox_03_out1 = 0;
                codebox_04_in1 = 0;
                codebox_04_in2 = 0;
                codebox_04_out1 = 0;
                numberobj_02_value = 0;
                numberobj_02_value_setter(numberobj_02_value);
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                signals[3] = nullptr;
                signals[4] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                cycle_tilde_01_wrap = 0;
                cycle_tilde_01_ph_currentPhase = 0;
                cycle_tilde_01_ph_conv = 0;
                cycle_tilde_01_setupDone = false;
                midiparse_01_parser_status = -1;
                midiparse_01_parser_byte1 = -1;
                tri_tilde_01_t = 0;
                tri_tilde_01_lastSyncPhase = 0;
                tri_tilde_01_lastSyncDiff = 0;
                tri_tilde_01_didSync = false;
                tri_tilde_01_yn = 0;
                tri_tilde_01_yn1 = 0;
                tri_tilde_01_yn2 = 0;
                tri_tilde_01_yn3 = 0;
                tri_tilde_01_flg = 0;
                tri_tilde_01_app_correction = 0;
                tri_tilde_01_dcblocker_xm1 = 0;
                tri_tilde_01_dcblocker_ym1 = 0;
                tri_tilde_01_setupDone = false;
                rect_tilde_01_xHistory = 0;
                rect_tilde_01_yHistory = 0;
                rect_tilde_01_t = 0;
                rect_tilde_01_lastSyncPhase = 0;
                rect_tilde_01_lastSyncDiff = 0;
                rect_tilde_01_didSync = false;
                saw_tilde_01_t = 0;
                saw_tilde_01_lastSyncPhase = 0;
                saw_tilde_01_lastSyncDiff = 0;
                saw_tilde_01_didSync = false;
                saw_tilde_01_dcblocker_xm1 = 0;
                saw_tilde_01_dcblocker_ym1 = 0;
                saw_tilde_01_setupDone = false;
                numberobj_02_currentFormat = 6;
                numberobj_02_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number dspexpr_03_in1;
                number dspexpr_03_in2;
                number p_01_target;
                number selector_02_onoff;
                number cycle_tilde_01_frequency;
                number cycle_tilde_01_phase_offset;
                number expr_01_in1;
                number expr_01_in2;
                number expr_01_out1;
                number codebox_02_in1;
                number codebox_02_in2;
                number codebox_02_out1;
                number unpack_01_out1;
                number unpack_01_out2;
                number tri_tilde_01_frequency;
                number tri_tilde_01_pulsewidth;
                number tri_tilde_01_syncPhase;
                number rect_tilde_01_frequency;
                number rect_tilde_01_pulsewidth;
                number rect_tilde_01_syncPhase;
                number saw_tilde_01_frequency;
                number saw_tilde_01_syncPhase;
                number codebox_03_in1;
                number codebox_03_out1;
                number codebox_04_in1;
                number codebox_04_in2;
                number codebox_04_out1;
                number numberobj_02_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[5];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                Float64BufferRef cycle_tilde_01_buffer;
                long cycle_tilde_01_wrap;
                uint32_t cycle_tilde_01_phasei;
                SampleValue cycle_tilde_01_f2i;
                number cycle_tilde_01_ph_currentPhase;
                number cycle_tilde_01_ph_conv;
                bool cycle_tilde_01_setupDone;
                int midiparse_01_parser_status;
                int midiparse_01_parser_byte1;
                number tri_tilde_01_t;
                number tri_tilde_01_lastSyncPhase;
                number tri_tilde_01_lastSyncDiff;
                bool tri_tilde_01_didSync;
                number tri_tilde_01_yn;
                number tri_tilde_01_yn1;
                number tri_tilde_01_yn2;
                number tri_tilde_01_yn3;
                number tri_tilde_01_flg;
                number tri_tilde_01_app_correction;
                number tri_tilde_01_dcblocker_xm1;
                number tri_tilde_01_dcblocker_ym1;
                bool tri_tilde_01_setupDone;
                number rect_tilde_01_xHistory;
                number rect_tilde_01_yHistory;
                number rect_tilde_01_t;
                number rect_tilde_01_lastSyncPhase;
                number rect_tilde_01_lastSyncDiff;
                bool rect_tilde_01_didSync;
                number saw_tilde_01_t;
                number saw_tilde_01_lastSyncPhase;
                number saw_tilde_01_lastSyncDiff;
                bool saw_tilde_01_didSync;
                number saw_tilde_01_dcblocker_xm1;
                number saw_tilde_01_dcblocker_ym1;
                bool saw_tilde_01_setupDone;
                Int numberobj_02_currentFormat;
                number numberobj_02_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                RNBOSubpatcher_25* p_01;
            
    };
    
    class RNBOSubpatcher_29 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_32;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_29()
            {
            }
            
            ~RNBOSubpatcher_29()
            {
            }
            
            virtual RNBOSubpatcher_32* getPatcher() const {
                return static_cast<RNBOSubpatcher_32 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, -1468824490, false);
            }
            
            Index vectorsize() const {
                return this->vs;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
            
                this->adsr_01_perform(
                    this->adsr_01_attack,
                    this->adsr_01_decay,
                    this->adsr_01_sustain,
                    this->adsr_01_release,
                    this->zeroBuffer,
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
                    this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->adsr_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case -1468824490:
                    {
                    this->adsr_01_mute_bang();
                    break;
                    }
                }
            }
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void eventinlet_11_out1_bang_bang() {}
            
            void eventinlet_11_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->midiparse_02_midiin_set(converted);
                }
            }
            
            void eventinlet_12_out1_bang_bang() {}
            
            void eventinlet_12_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_01_attack_set(converted);
                }
            }
            
            void eventinlet_13_out1_bang_bang() {}
            
            void eventinlet_13_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_01_decay_set(converted);
                }
            }
            
            void eventinlet_14_out1_bang_bang() {}
            
            void eventinlet_14_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_01_sustain_set(converted);
                }
            }
            
            void eventinlet_15_out1_bang_bang() {}
            
            void eventinlet_15_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_01_release_set(converted);
                }
            }
            
            void adsr_01_mute_bang() {}
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void adsr_01_attack_set(number v) {
                this->adsr_01_attack = v;
            }
            
            void eventinlet_12_out1_number_set(number v) {
                this->adsr_01_attack_set(v);
            }
            
            void adsr_01_decay_set(number v) {
                this->adsr_01_decay = v;
            }
            
            void eventinlet_13_out1_number_set(number v) {
                this->adsr_01_decay_set(v);
            }
            
            void adsr_01_sustain_set(number v) {
                this->adsr_01_sustain = v;
            }
            
            void eventinlet_14_out1_number_set(number v) {
                this->adsr_01_sustain_set(v);
            }
            
            void adsr_01_release_set(number v) {
                this->adsr_01_release = v;
            }
            
            void eventinlet_15_out1_number_set(number v) {
                this->adsr_01_release_set(v);
            }
            
            void midiparse_02_channel_set(number ) {}
            
            void adsr_01_trigger_number_set(number v) {
                this->adsr_01_trigger_number = v;
            
                if (v != 0)
                    this->adsr_01_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;
            
                for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
                    this->adsr_01_triggerValueBuf[(Index)i] = v;
                }
            }
            
            void expr_02_out1_set(number v) {
                this->expr_02_out1 = v;
                this->adsr_01_trigger_number_set(this->expr_02_out1);
            }
            
            void expr_02_in1_set(number in1) {
                this->expr_02_in1 = in1;
            
                this->expr_02_out1_set(
                    (this->expr_02_in2 == 0 ? 0 : (this->expr_02_in2 == 0. ? 0. : this->expr_02_in1 / this->expr_02_in2))
                );//#map:EnvelopeI//_obj-36:1
            }
            
            void unpack_02_out2_set(number v) {
                this->unpack_02_out2 = v;
                this->expr_02_in1_set(v);
            }
            
            void unpack_02_out1_set(number v) {
                this->unpack_02_out1 = v;
            }
            
            void unpack_02_input_list_set(const list& v) {
                if (v->length > 1)
                    this->unpack_02_out2_set(trunc(v[1]));
            
                if (v->length > 0)
                    this->unpack_02_out1_set(trunc(v[0]));
            }
            
            void midiparse_02_noteonoroff_set(const list& v) {
                this->unpack_02_input_list_set(v);
            }
            
            void midiparse_02_polypressure_set(const list& ) {}
            
            void midiparse_02_controlchange_set(const list& ) {}
            
            void midiparse_02_programchange_set(number ) {}
            
            void midiparse_02_aftertouch_set(number ) {}
            
            void midiparse_02_pitchbend_set(number ) {}
            
            void midiparse_02_midiin_set(number midivalue) {
                list result = this->midiparse_02_parser_next(midivalue);
            
                switch ((int)result[0]) {
                case 0:
                    {
                    this->midiparse_02_channel_set(result[3]);
                    this->midiparse_02_noteonoroff_set({result[1], result[2]});
                    break;
                    }
                case 1:
                    {
                    this->midiparse_02_channel_set(result[3]);
                    this->midiparse_02_polypressure_set({result[1], result[2]});
                    break;
                    }
                case 2:
                    {
                    this->midiparse_02_channel_set(result[3]);
                    this->midiparse_02_controlchange_set({result[1], result[2]});
                    break;
                    }
                case 3:
                    {
                    this->midiparse_02_channel_set(result[2]);
                    this->midiparse_02_programchange_set(result[1]);
                    break;
                    }
                case 4:
                    {
                    this->midiparse_02_channel_set(result[2]);
                    this->midiparse_02_aftertouch_set(result[1]);
                    break;
                    }
                case 5:
                    {
                    this->midiparse_02_channel_set(result[2]);
                    this->midiparse_02_pitchbend_set(result[1]);
                    break;
                    }
                }
            }
            
            void eventinlet_11_out1_number_set(number v) {
                this->midiparse_02_midiin_set(v);
            }
            
            void adsr_01_perform(
                number attack,
                number decay,
                number sustain,
                number release,
                const SampleValue * trigger_signal,
                SampleValue * out,
                Index n
            ) {
                RNBO_UNUSED(trigger_signal);
                auto __adsr_01_trigger_number = this->adsr_01_trigger_number;
                auto __adsr_01_time = this->adsr_01_time;
                auto __adsr_01_amplitude = this->adsr_01_amplitude;
                auto __adsr_01_outval = this->adsr_01_outval;
                auto __adsr_01_startingpoint = this->adsr_01_startingpoint;
                auto __adsr_01_phase = this->adsr_01_phase;
                auto __adsr_01_legato = this->adsr_01_legato;
                auto __adsr_01_lastTriggerVal = this->adsr_01_lastTriggerVal;
                auto __adsr_01_maxsustain = this->adsr_01_maxsustain;
                auto __adsr_01_mspersamp = this->adsr_01_mspersamp;
                bool bangMute = false;
            
                for (Index i = 0; i < n; i++) {
                    number clampedattack = (attack > __adsr_01_mspersamp ? attack : __adsr_01_mspersamp);
                    number clampeddecay = (decay > __adsr_01_mspersamp ? decay : __adsr_01_mspersamp);
                    number clampedsustain = (__adsr_01_maxsustain > __adsr_01_mspersamp ? __adsr_01_maxsustain : __adsr_01_mspersamp);
                    number clampedrelease = (release > __adsr_01_mspersamp ? release : __adsr_01_mspersamp);
                    number currentTriggerVal = this->adsr_01_triggerValueBuf[(Index)i];
            
                    if ((__adsr_01_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_01_triggerBuf[(Index)i] == 1) {
                        if ((bool)(__adsr_01_legato)) {
                            if (__adsr_01_phase != 0) {
                                __adsr_01_startingpoint = __adsr_01_outval;
                            } else {
                                __adsr_01_startingpoint = 0;
                            }
                        } else {
                            __adsr_01_startingpoint = 0;
                        }
            
                        __adsr_01_amplitude = currentTriggerVal;
                        __adsr_01_phase = 1;
                        __adsr_01_time = 0.0;
                        bangMute = false;
                    } else if (__adsr_01_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
                        if (__adsr_01_phase != 4 && __adsr_01_phase != 0) {
                            __adsr_01_phase = 4;
                            __adsr_01_amplitude = __adsr_01_outval;
                            __adsr_01_time = 0.0;
                        }
                    }
            
                    __adsr_01_time += __adsr_01_mspersamp;
            
                    if (__adsr_01_phase == 0) {
                        __adsr_01_outval = 0;
                    } else if (__adsr_01_phase == 1) {
                        if (__adsr_01_time > clampedattack) {
                            __adsr_01_time -= clampedattack;
                            __adsr_01_phase = 2;
                            __adsr_01_outval = __adsr_01_amplitude;
                        } else {
                            __adsr_01_outval = (__adsr_01_amplitude - __adsr_01_startingpoint) * __adsr_01_time / clampedattack + __adsr_01_startingpoint;
                        }
                    } else if (__adsr_01_phase == 2) {
                        if (__adsr_01_time > clampeddecay) {
                            __adsr_01_time -= clampeddecay;
                            __adsr_01_phase = 3;
                            __adsr_01_outval = __adsr_01_amplitude * sustain;
                        } else {
                            __adsr_01_outval = __adsr_01_amplitude * sustain + (__adsr_01_amplitude - __adsr_01_amplitude * sustain) * (1. - __adsr_01_time / clampeddecay);
                        }
                    } else if (__adsr_01_phase == 3) {
                        if (__adsr_01_time > clampedsustain && __adsr_01_maxsustain > -1) {
                            __adsr_01_time -= clampedsustain;
                            __adsr_01_phase = 4;
                            __adsr_01_amplitude = __adsr_01_outval;
                        } else {
                            __adsr_01_outval = __adsr_01_amplitude * sustain;
                        }
                    } else if (__adsr_01_phase == 4) {
                        if (__adsr_01_time > clampedrelease) {
                            __adsr_01_time = 0;
                            __adsr_01_phase = 0;
                            __adsr_01_outval = 0;
                            __adsr_01_amplitude = 0;
                            bangMute = true;
                        } else {
                            __adsr_01_outval = __adsr_01_amplitude * (1.0 - __adsr_01_time / clampedrelease);
                        }
                    }
            
                    out[(Index)i] = __adsr_01_outval;
                    this->adsr_01_triggerBuf[(Index)i] = 0;
                    this->adsr_01_triggerValueBuf[(Index)i] = __adsr_01_trigger_number;
                    __adsr_01_lastTriggerVal = currentTriggerVal;
                }
            
                if ((bool)(bangMute)) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -1468824490,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;
                }
            
                this->adsr_01_lastTriggerVal = __adsr_01_lastTriggerVal;
                this->adsr_01_phase = __adsr_01_phase;
                this->adsr_01_startingpoint = __adsr_01_startingpoint;
                this->adsr_01_outval = __adsr_01_outval;
                this->adsr_01_amplitude = __adsr_01_amplitude;
                this->adsr_01_time = __adsr_01_time;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            list midiparse_02_parser_next(number midiin) {
                int midivalue = (int)(trunc(midiin));
                list result = list(-1);
                number resetByte1 = false;
            
                if (midivalue > 127) {
                    this->midiparse_02_parser_status = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0xFF);
                    this->midiparse_02_parser_byte1 = -1;
                } else {
                    switch ((int)((BinOpInt)this->midiparse_02_parser_status & (BinOpInt)0xF0)) {
                    case 0xB0:
                        {
                        if (this->midiparse_02_parser_byte1 == -1) {
                            this->midiparse_02_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                2,
                                this->midiparse_02_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_02_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xA0:
                        {
                        if (this->midiparse_02_parser_byte1 == -1) {
                            this->midiparse_02_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                1,
                                this->midiparse_02_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_02_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xE0:
                        {
                        if (this->midiparse_02_parser_byte1 == -1) {
                            this->midiparse_02_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            number pitchbend;
            
                            {
                                number val = this->midiparse_02_parser_byte1 + ((BinOpInt)(((BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32)));
            
                                {
                                    val -= 0x2000;
                                    pitchbend = val / (number)8192;
                                }
                            }
            
                            result = {
                                5,
                                pitchbend,
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_02_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xD0:
                        {
                        result = {
                            4,
                            (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                            (BinOpInt)((BinOpInt)(1 + this->midiparse_02_parser_status) & (BinOpInt)0x0F)
                        };
            
                        break;
                        }
                    case 0x90:
                        {
                        if (this->midiparse_02_parser_byte1 == -1) {
                            this->midiparse_02_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                0,
                                this->midiparse_02_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_02_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xC0:
                        {
                        result = {
                            3,
                            (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                            (BinOpInt)((BinOpInt)(1 + this->midiparse_02_parser_status) & (BinOpInt)0x0F)
                        };
            
                        break;
                        }
                    case 0x80:
                        {
                        if (this->midiparse_02_parser_byte1 == -1) {
                            this->midiparse_02_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                0,
                                this->midiparse_02_parser_byte1,
                                0,
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_02_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    default:
                        {
                        result = {-1};
                        }
                    }
                }
            
                if (result->length > 1) {
                    result->push(this->midiparse_02_parser_status);
                    result->push(this->midiparse_02_parser_byte1);
                    result->push(midivalue);
                }
            
                if ((bool)(resetByte1)) {
                    this->midiparse_02_parser_byte1 = -1;
                }
            
                return result;
            }
            
            void midiparse_02_parser_reset() {
                this->midiparse_02_parser_status = -1;
                this->midiparse_02_parser_byte1 = -1;
            }
            
            void adsr_01_dspsetup(bool force) {
                if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->adsr_01_mspersamp = (number)1000 / this->sr;
                this->adsr_01_setupDone = true;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                expr_02_in1 = 0;
                expr_02_in2 = 127;
                expr_02_out1 = 0;
                unpack_02_out1 = 0;
                unpack_02_out2 = 0;
                adsr_01_trigger_number = 0;
                adsr_01_attack = 0;
                adsr_01_decay = 0;
                adsr_01_sustain = 0;
                adsr_01_release = 0;
                adsr_01_legato = 0;
                adsr_01_maxsustain = -1;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                midiparse_02_parser_status = -1;
                midiparse_02_parser_byte1 = -1;
                adsr_01_phase = 3;
                adsr_01_mspersamp = 0;
                adsr_01_time = 0;
                adsr_01_lastTriggerVal = 0;
                adsr_01_amplitude = 0;
                adsr_01_outval = 0;
                adsr_01_startingpoint = 0;
                adsr_01_triggerBuf = nullptr;
                adsr_01_triggerValueBuf = nullptr;
                adsr_01_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number expr_02_in1;
                number expr_02_in2;
                number expr_02_out1;
                number unpack_02_out1;
                number unpack_02_out2;
                number adsr_01_trigger_number;
                number adsr_01_attack;
                number adsr_01_decay;
                number adsr_01_sustain;
                number adsr_01_release;
                number adsr_01_legato;
                number adsr_01_maxsustain;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                int midiparse_02_parser_status;
                int midiparse_02_parser_byte1;
                Int adsr_01_phase;
                number adsr_01_mspersamp;
                number adsr_01_time;
                number adsr_01_lastTriggerVal;
                number adsr_01_amplitude;
                number adsr_01_outval;
                number adsr_01_startingpoint;
                signal adsr_01_triggerBuf;
                signal adsr_01_triggerValueBuf;
                bool adsr_01_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_30 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_32;
            friend class rnbomatic;
            
            public:
            
            class RNBOSubpatcher_26 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_30;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_26()
                        {
                        }
                        
                        ~RNBOSubpatcher_26()
                        {
                        }
                        
                        virtual RNBOSubpatcher_30* getPatcher() const {
                            return static_cast<RNBOSubpatcher_30 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
                            getEngine()->flushClockEvents(this, 848255507, false);
                        }
                        
                        MillisecondTime currenttime() {
                            return this->_currentTime;
                        }
                        
                        Index getNumMidiInputPorts() const {
                            return 0;
                        }
                        
                        void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
                        
                        Index getNumMidiOutputPorts() const {
                            return 0;
                        }
                        
                        void process(
                            const SampleValue * const* inputs,
                            Index numInputs,
                            SampleValue * const* outputs,
                            Index numOutputs,
                            Index n
                        ) {
                            RNBO_UNUSED(numOutputs);
                            RNBO_UNUSED(outputs);
                            RNBO_UNUSED(numInputs);
                            RNBO_UNUSED(inputs);
                            this->vs = n;
                            this->updateTime(this->getEngine()->getCurrentTime());
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                                this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                                this->didAllocateSignals = true;
                            }
                        
                            const bool sampleRateChanged = sampleRate != this->sr;
                            const bool maxvsChanged = maxBlockSize != this->maxvs;
                            const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
                        
                            if (sampleRateChanged || maxvsChanged) {
                                this->vs = maxBlockSize;
                                this->maxvs = maxBlockSize;
                                this->sr = sampleRate;
                                this->invsr = 1 / sampleRate;
                            }
                        
                            RNBO_UNUSED(forceDSPSetup);
                        
                            if (sampleRateChanged)
                                this->onSampleRateChanged(sampleRate);
                        }
                        
                        void setProbingTarget(MessageTag id) {
                            switch (id) {
                            default:
                                {
                                this->setProbingIndex(-1);
                                break;
                                }
                            }
                        }
                        
                        void setProbingIndex(ProbingIndex ) {}
                        
                        Index getProbingChannels(MessageTag outletId) const {
                            RNBO_UNUSED(outletId);
                            return 0;
                        }
                        
                        void setVoiceIndex(Index index)  {
                            this->_voiceIndex = index;
                        }
                        
                        void setNoteNumber(Int noteNumber)  {
                            this->_noteNumber = noteNumber;
                        }
                        
                        Index getIsMuted()  {
                            return this->isMuted;
                        }
                        
                        void setIsMuted(Index v)  {
                            this->isMuted = v;
                        }
                        
                        void onSampleRateChanged(double ) {}
                        
                        Index getPatcherSerial() const {
                            return 0;
                        }
                        
                        void getState(PatcherStateInterface& ) {}
                        
                        void setState() {}
                        
                        void getPreset(PatcherStateInterface& ) {}
                        
                        void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
                        
                        void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValue(index, value, time);
                        }
                        
                        void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                            this->setParameterValue(index, this->getParameterValue(index), time);
                        }
                        
                        void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValueNormalized(index, value, time);
                        }
                        
                        ParameterValue getParameterValue(ParameterIndex index)  {
                            switch (index) {
                            default:
                                {
                                return 0;
                                }
                            }
                        }
                        
                        ParameterIndex getNumSignalInParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumSignalOutParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumParameters() const {
                            return 0;
                        }
                        
                        ConstCharPointer getParameterName(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        ConstCharPointer getParameterId(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
                        
                        void sendParameter(ParameterIndex index, bool ignoreValue) {
                            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
                        }
                        
                        void setParameterOffset(ParameterIndex offset) {
                            this->parameterOffset = offset;
                        }
                        
                        ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                            if (steps == 1) {
                                if (normalizedValue > 0) {
                                    normalizedValue = 1.;
                                }
                            } else {
                                ParameterValue oneStep = (number)1. / (steps - 1);
                                ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                                normalizedValue = numberOfSteps * oneStep;
                            }
                        
                            return normalizedValue;
                        }
                        
                        ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        void scheduleParamInit(ParameterIndex index, Index order) {
                            this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
                        }
                        
                        void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                            RNBO_UNUSED(hasValue);
                            this->updateTime(time);
                        
                            switch (index) {
                            case 848255507:
                                {
                                this->line_02_tick_set(value);
                                break;
                                }
                            }
                        }
                        
                        void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
                        
                        void processOutletEvent(
                            EngineLink* sender,
                            OutletIndex index,
                            ParameterValue value,
                            MillisecondTime time
                        ) {
                            this->updateTime(time);
                            this->processOutletAtCurrentTime(sender, index, value);
                        }
                        
                        void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                            this->updateTime(time);
                        
                            switch (tag) {
                            case TAG("valin"):
                                {
                                if (TAG("poly/OscillatorII/BendFreq/number_obj-22") == objectId)
                                    this->numberobj_03_valin_set(payload);
                        
                                break;
                                }
                            case TAG("format"):
                                {
                                if (TAG("poly/OscillatorII/BendFreq/number_obj-22") == objectId)
                                    this->numberobj_03_format_set(payload);
                        
                                break;
                                }
                            }
                        }
                        
                        void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
                        
                        void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
                        
                        MessageTagInfo resolveTag(MessageTag tag) const {
                            switch (tag) {
                            case TAG("valout"):
                                {
                                return "valout";
                                }
                            case TAG("poly/OscillatorII/BendFreq/number_obj-22"):
                                {
                                return "poly/OscillatorII/BendFreq/number_obj-22";
                                }
                            case TAG("setup"):
                                {
                                return "setup";
                                }
                            case TAG("valin"):
                                {
                                return "valin";
                                }
                            case TAG("format"):
                                {
                                return "format";
                                }
                            }
                        
                            return nullptr;
                        }
                        
                        DataRef* getDataRef(DataRefIndex index)  {
                            switch (index) {
                            default:
                                {
                                return nullptr;
                                }
                            }
                        }
                        
                        DataRefIndex getNumDataRefs() const {
                            return 0;
                        }
                        
                        void fillDataRef(DataRefIndex , DataRef& ) {}
                        
                        void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                        }
                        
                        protected:
                        
                        void eventinlet_16_out1_bang_bang() {
                            this->pak_02_in1_bang();
                        }
                        
                        void eventinlet_16_out1_list_set(const list& v) {
                            {
                                if (v->length > 3)
                                    this->pak_02_in4_set(v[3]);
                        
                                if (v->length > 2)
                                    this->pak_02_in3_set(v[2]);
                        
                                if (v->length > 1)
                                    this->pak_02_in2_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->pak_02_in1_set(converted);
                            }
                        }
                        
                        void line_02_tick_set(number v) {
                            this->line_02_output_set(v);
                        
                            if ((bool)(this->line_02_isFinished(v))) {
                                this->line_02_slope = 0;
                                this->line_02_startValue = v;
                                this->line_02_startPendingRamp();
                            } else {
                                this->line_02_scheduleNext();
                            }
                        }
                        
                        void eventinlet_17_out1_bang_bang() {
                            this->pak_02_in2_bang();
                        }
                        
                        void eventinlet_17_out1_list_set(const list& v) {
                            {
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->pak_02_in2_set(converted);
                            }
                        }
                        
                        void numberobj_03_valin_set(number v) {
                            this->numberobj_03_value_set(v);
                        }
                        
                        void numberobj_03_format_set(number v) {
                            this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
                        }
                        
                        void eventinlet_18_out1_bang_bang() {
                            this->pak_02_in3_bang();
                        }
                        
                        void eventinlet_18_out1_list_set(const list& v) {
                            {
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->pak_02_in3_set(converted);
                            }
                        }
                        
                        void eventinlet_19_out1_bang_bang() {
                            this->pak_02_in4_bang();
                        }
                        
                        void eventinlet_19_out1_list_set(const list& v) {
                            {
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->pak_02_in4_set(converted);
                            }
                        }
                        
                        number msToSamps(MillisecondTime ms, number sampleRate) {
                            return ms * sampleRate * 0.001;
                        }
                        
                        MillisecondTime sampsToMs(SampleIndex samps) {
                            return samps * (this->invsr * 1000);
                        }
                        
                        Index getMaxBlockSize() const {
                            return this->maxvs;
                        }
                        
                        number getSampleRate() const {
                            return this->sr;
                        }
                        
                        bool hasFixedVectorSize() const {
                            return false;
                        }
                        
                        Index getNumInputChannels() const {
                            return 0;
                        }
                        
                        Index getNumOutputChannels() const {
                            return 0;
                        }
                        
                        void initializeObjects() {
                            this->numberobj_03_init();
                        }
                        
                        void sendOutlet(OutletIndex index, ParameterValue value) {
                            this->getEngine()->sendOutlet(this, index, value);
                        }
                        
                        void startup() {}
                        
                        void allocateDataRefs() {}
                        
                        number line_02_time_constrain(number v) const {
                            if (v < 0)
                                v = 0;
                        
                            return v;
                        }
                        
                        void line_02_time_set(number v) {
                            v = this->line_02_time_constrain(v);
                            this->line_02_time = v;
                        }
                        
                        void numberobj_03_output_set(number ) {}
                        
                        void numberobj_03_value_set(number v) {
                            this->numberobj_03_value_setter(v);
                            v = this->numberobj_03_value;
                            number localvalue = v;
                        
                            if (this->numberobj_03_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->getEngine()->sendNumMessage(
                                TAG("valout"),
                                TAG("poly/OscillatorII/BendFreq/number_obj-22"),
                                localvalue,
                                this->_currentTime
                            );
                        
                            this->numberobj_03_output_set(localvalue);
                        }
                        
                        void eventoutlet_02_in1_number_set(number v) {
                            this->getPatcher()->updateTime(this->_currentTime);
                            this->getPatcher()->p_02_out1_number_set(v);
                        }
                        
                        void line_02_output_set(number v) {
                            this->line_02_output = v;
                            this->numberobj_03_value_set(v);
                            this->eventoutlet_02_in1_number_set(v);
                        }
                        
                        void line_02_stop_bang() {
                            this->getEngine()->flushClockEvents(this, 848255507, false);;
                            this->line_02_pendingRamps->length = 0;
                            this->line_02_startValue = this->line_02_output;
                            this->line_02_slope = 0;
                            this->line_02__time = 0;
                            this->line_02_time_set(0);
                        }
                        
                        number line_02_grain_constrain(number v) const {
                            if (v < 0)
                                v = 0;
                        
                            return v;
                        }
                        
                        void line_02_grain_set(number v) {
                            v = this->line_02_grain_constrain(v);
                            this->line_02_grain = v;
                        
                            if ((bool)(!(bool)(this->line_02_isFinished(this->line_02_startValue)))) {
                                this->getEngine()->flushClockEvents(this, 848255507, false);;
                                this->line_02_scheduleNext();
                            }
                        }
                        
                        void line_02_end_bang() {}
                        
                        void line_02_target_set(const list& v) {
                            this->line_02_target = jsCreateListCopy(v);
                            this->line_02_pendingRamps->length = 0;
                        
                            if (v->length == 1) {
                                this->line_02__time = this->line_02_time;
                                this->line_02_time_set(0);
                        
                                if ((bool)(this->line_02__time)) {
                                    this->line_02_startRamp(v[0], this->line_02__time);
                                } else {
                                    this->line_02_output_set(v[0]);
                                    this->line_02_startValue = v[0];
                                    this->line_02_stop_bang();
                                }
                            } else if (v->length == 2) {
                                this->line_02_time_set(0);
                                this->line_02__time = (v[1] < 0 ? 0 : v[1]);
                                this->line_02_startRamp(v[0], this->line_02__time);
                            } else if (v->length == 3) {
                                this->line_02_time_set(0);
                                this->line_02_grain_set(v[2]);
                                this->line_02__time = (v[1] < 0 ? 0 : v[1]);
                                this->line_02_startRamp(v[0], this->line_02__time);
                            } else {
                                this->line_02_time_set(0);
                                this->line_02_pendingRamps = jsCreateListCopy(v);
                                this->line_02_startPendingRamp();
                            }
                        }
                        
                        void codebox_05_out2_set(number v) {
                            this->codebox_05_out2 = v;
                        
                            {
                                list converted = {this->codebox_05_out2};
                                this->line_02_target_set(converted);
                            }
                        }
                        
                        void codebox_05_in1_set(const list& in1) {
                            this->codebox_05_in1 = jsCreateListCopy(in1);
                            number x = this->codebox_05_in1[0];
                            number y = this->codebox_05_in1[1];
                            number z = this->codebox_05_in1[2];
                            number bendFactor = this->codebox_05_in1[3];
                        
                            if (bendFactor >= 0) {
                                this->codebox_05_out2_set(y + bendFactor * (z - y));//#map:_###_obj_###_:6
                            } else {
                                this->codebox_05_out2_set(x + -bendFactor * (x - y));//#map:_###_obj_###_:8
                            }//#map:OscillatorII/BendFreq/codebox_obj-12:5
                        }
                        
                        void pak_02_out_set(const list& v) {
                            this->codebox_05_in1_set(v);
                        }
                        
                        void pak_02_in3_set(number v) {
                            this->pak_02_in3 = v;
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_02_in1);
                            array[1] = trunc(this->pak_02_in2);
                            array[2] = trunc(this->pak_02_in3);
                            array[3] = this->pak_02_in4;
                            this->pak_02_out_set(array);
                        }
                        
                        void eventinlet_18_out1_number_set(number v) {
                            this->pak_02_in3_set(v);
                        }
                        
                        void pak_02_in2_set(number v) {
                            this->pak_02_in2 = v;
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_02_in1);
                            array[1] = trunc(this->pak_02_in2);
                            array[2] = trunc(this->pak_02_in3);
                            array[3] = this->pak_02_in4;
                            this->pak_02_out_set(array);
                        }
                        
                        void eventinlet_17_out1_number_set(number v) {
                            this->pak_02_in2_set(v);
                        }
                        
                        void pak_02_in1_set(number v) {
                            this->pak_02_in1 = v;
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_02_in1);
                            array[1] = trunc(this->pak_02_in2);
                            array[2] = trunc(this->pak_02_in3);
                            array[3] = this->pak_02_in4;
                            this->pak_02_out_set(array);
                        }
                        
                        void eventinlet_16_out1_number_set(number v) {
                            this->pak_02_in1_set(v);
                        }
                        
                        void pak_02_in4_set(number v) {
                            this->pak_02_in4 = v;
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_02_in1);
                            array[1] = trunc(this->pak_02_in2);
                            array[2] = trunc(this->pak_02_in3);
                            array[3] = this->pak_02_in4;
                            this->pak_02_out_set(array);
                        }
                        
                        void eventinlet_19_out1_number_set(number v) {
                            this->pak_02_in4_set(v);
                        }
                        
                        void pak_02_in1_bang() {
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_02_in1);
                            array[1] = trunc(this->pak_02_in2);
                            array[2] = trunc(this->pak_02_in3);
                            array[3] = this->pak_02_in4;
                            this->pak_02_out_set(array);
                        }
                        
                        void pak_02_in2_bang() {
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_02_in1);
                            array[1] = trunc(this->pak_02_in2);
                            array[2] = trunc(this->pak_02_in3);
                            array[3] = this->pak_02_in4;
                            this->pak_02_out_set(array);
                        }
                        
                        void pak_02_in3_bang() {
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_02_in1);
                            array[1] = trunc(this->pak_02_in2);
                            array[2] = trunc(this->pak_02_in3);
                            array[3] = this->pak_02_in4;
                            this->pak_02_out_set(array);
                        }
                        
                        void pak_02_in4_bang() {
                            list array = list(0, 0, 0, 0);
                            array[0] = trunc(this->pak_02_in1);
                            array[1] = trunc(this->pak_02_in2);
                            array[2] = trunc(this->pak_02_in3);
                            array[3] = this->pak_02_in4;
                            this->pak_02_out_set(array);
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
                        }
                        
                        void numberobj_03_value_setter(number v) {
                            number localvalue = v;
                        
                            if (this->numberobj_03_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->numberobj_03_value = localvalue;
                        }
                        
                        number line_02_valueAtTime(MillisecondTime time) {
                            return this->line_02_startValue + this->line_02_slope * (time - this->line_02_startTime);
                        }
                        
                        void line_02_scheduleNext() {
                            MillisecondTime currentTime = (MillisecondTime)(this->currenttime());
                            number nextTime = currentTime + this->line_02_grain;
                            number nextValue;
                        
                            if (nextTime - this->line_02_startTime >= this->line_02__time || this->line_02_grain == 0) {
                                nextTime = this->line_02_startTime + this->line_02__time;
                                nextValue = this->line_02_currentTarget;
                            } else {
                                nextValue = this->line_02_valueAtTime(nextTime);
                            }
                        
                            this->getEngine()->scheduleClockEventWithValue(this, 848255507, nextTime - currentTime + this->_currentTime, nextValue);;
                        }
                        
                        void line_02_startRamp(number target, MillisecondTime time) {
                            MillisecondTime currentTime = (MillisecondTime)(this->currenttime());
                            this->line_02_startValue = this->line_02_valueAtTime(currentTime);
                            this->line_02_startTime = currentTime;
                            this->line_02_currentTarget = target;
                            this->getEngine()->flushClockEvents(this, 848255507, false);;
                            number rise = target - this->line_02_startValue;
                            this->line_02_slope = rise / time;
                            this->line_02_scheduleNext();
                        }
                        
                        bool line_02_isFinished(number value) {
                            return value == this->line_02_currentTarget && this->currenttime() - this->line_02_startTime >= this->line_02__time;
                        }
                        
                        void line_02_startPendingRamp() {
                            if (this->line_02_pendingRamps->length < 2) {
                                this->line_02_pendingRamps->length = 0;
                                this->line_02__time = 0;
                                this->line_02_time_set(0);
                                this->line_02_end_bang();
                                return;
                            }
                        
                            if (this->line_02_pendingRamps->length > 1) {
                                number target = this->line_02_pendingRamps->shift();
                                this->line_02__time = this->line_02_pendingRamps->shift();
                                this->line_02__time = (this->line_02__time < 0 ? 0 : this->line_02__time);
                                this->line_02_startRamp(target, this->line_02__time);
                            }
                        }
                        
                        void numberobj_03_init() {
                            this->numberobj_03_currentFormat = 6;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/OscillatorII/BendFreq/number_obj-22"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
                            preset["value"] = this->numberobj_03_value;
                        }
                        
                        void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
                            if ((bool)(stateIsEmpty(preset)))
                                return;
                        
                            this->numberobj_03_value_set(preset["value"]);
                        }
                        
                        bool stackprotect_check() {
                            this->stackprotect_count++;
                        
                            if (this->stackprotect_count > 128) {
                                console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                                return true;
                            }
                        
                            return false;
                        }
                        
                        void updateTime(MillisecondTime time) {
                            this->_currentTime = time;
                            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
                        
                            if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
                        
                            if (this->sampleOffsetIntoNextAudioBuffer < 0)
                                this->sampleOffsetIntoNextAudioBuffer = 0;
                        }
                        
                        void assign_defaults()
                        {
                            line_02_time = 0;
                            line_02_grain = 20;
                            line_02_output = 0;
                            codebox_05_out2 = 0;
                            pak_02_in1 = 0;
                            pak_02_in2 = 0;
                            pak_02_in3 = 0;
                            pak_02_in4 = 0;
                            numberobj_03_value = 0;
                            numberobj_03_value_setter(numberobj_03_value);
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            line_02_startTime = 0;
                            line_02_startValue = 20;
                            line_02_currentTarget = 0;
                            line_02_slope = 0;
                            line_02__time = 0;
                            numberobj_03_currentFormat = 6;
                            numberobj_03_lastValue = 0;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            list line_02_target;
                            number line_02_time;
                            number line_02_grain;
                            number line_02_output;
                            list codebox_05_in1;
                            number codebox_05_out2;
                            number pak_02_in1;
                            number pak_02_in2;
                            number pak_02_in3;
                            number pak_02_in4;
                            number numberobj_03_value;
                            MillisecondTime _currentTime;
                            UInt64 audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            MillisecondTime line_02_startTime;
                            number line_02_startValue;
                            number line_02_currentTarget;
                            number line_02_slope;
                            MillisecondTime line_02__time;
                            list line_02_pendingRamps;
                            Int numberobj_03_currentFormat;
                            number numberobj_03_lastValue;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            RNBOSubpatcher_30()
            {
            }
            
            ~RNBOSubpatcher_30()
            {
                delete this->p_02;
            }
            
            virtual RNBOSubpatcher_32* getPatcher() const {
                return static_cast<RNBOSubpatcher_32 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            number samplerate() const {
                return this->sr;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                this->p_02_perform(n);
            
                this->cycle_tilde_02_perform(
                    this->cycle_tilde_02_frequency,
                    this->cycle_tilde_02_phase_offset,
                    this->signals[0],
                    this->dummyBuffer,
                    n
                );
            
                this->tri_tilde_02_perform(
                    this->tri_tilde_02_frequency,
                    this->tri_tilde_02_pulsewidth,
                    this->tri_tilde_02_syncPhase,
                    this->signals[1],
                    this->dummyBuffer,
                    n
                );
            
                this->rect_tilde_02_perform(
                    this->rect_tilde_02_frequency,
                    this->rect_tilde_02_pulsewidth,
                    this->rect_tilde_02_syncPhase,
                    this->signals[2],
                    this->dummyBuffer,
                    n
                );
            
                this->saw_tilde_02_perform(
                    this->saw_tilde_02_frequency,
                    this->saw_tilde_02_syncPhase,
                    this->signals[3],
                    this->dummyBuffer,
                    n
                );
            
                this->selector_03_perform(
                    this->selector_03_onoff,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    this->signals[3],
                    this->signals[4],
                    n
                );
            
                this->dspexpr_04_perform(this->signals[4], this->dspexpr_04_in2, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 5; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->cycle_tilde_02_dspsetup(forceDSPSetup);
                this->tri_tilde_02_dspsetup(forceDSPSetup);
                this->saw_tilde_02_dspsetup(forceDSPSetup);
                this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
                this->p_02->setVoiceIndex(index);
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
                this->p_02->setNoteNumber(noteNumber);
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {
                this->p_02 = new RNBOSubpatcher_26();
                this->p_02->setEngineAndPatcher(this->getEngine(), this);
                this->p_02->initialize();
                this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
            }
            
            void getPreset(PatcherStateInterface& preset) {
                this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "BendFreq"));
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                RNBO_UNUSED(v);
                this->updateTime(time);
            
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_02->getNumParameters())
                        this->p_02->setParameterValue(index, v, time);
            
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->getParameterValue(index);
            
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0 + this->p_02->getNumParameters();
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->getParameterName(index);
            
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->getParameterId(index);
            
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    default:
                        {
                        index -= 0;
            
                        if (index < this->p_02->getNumParameters())
                            this->p_02->getParameterInfo(index, info);
            
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
                if (subpatcher == this->p_02)
                    return 0;
            
                return 0;
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->convertToNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->convertFromNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->constrainParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("valin"):
                    {
                    if (TAG("poly/OscillatorII/number_obj-24") == objectId)
                        this->numberobj_04_valin_set(payload);
            
                    break;
                    }
                case TAG("format"):
                    {
                    if (TAG("poly/OscillatorII/number_obj-24") == objectId)
                        this->numberobj_04_format_set(payload);
            
                    break;
                    }
                }
            
                this->p_02->processNumMessage(tag, objectId, time, payload);
            }
            
            void processListMessage(
                MessageTag tag,
                MessageTag objectId,
                MillisecondTime time,
                const list& payload
            ) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_02->processListMessage(tag, objectId, time, payload);
            }
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_02->processBangMessage(tag, objectId, time);
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
                case TAG("valout"):
                    {
                    return "valout";
                    }
                case TAG("poly/OscillatorII/number_obj-24"):
                    {
                    return "poly/OscillatorII/number_obj-24";
                    }
                case TAG("setup"):
                    {
                    return "setup";
                    }
                case TAG("valin"):
                    {
                    return "valin";
                    }
                case TAG("format"):
                    {
                    return "format";
                    }
                }
            
                auto subpatchResult_0 = this->p_02->resolveTag(tag);
            
                if (subpatchResult_0)
                    return subpatchResult_0;
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 0) {
                    this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
                    this->cycle_tilde_02_bufferUpdated();
                }
            
                this->p_02->processDataViewUpdate(index, time);
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
                this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
            }
            
            protected:
            
            void eventinlet_20_out1_bang_bang() {}
            
            void eventinlet_20_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->midiparse_03_midiin_set(converted);
                }
            }
            
            void eventinlet_21_out1_bang_bang() {}
            
            void eventinlet_21_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->selector_03_onoff_set(converted);
                }
            }
            
            void eventinlet_22_out1_bang_bang() {
                this->expr_03_in2_bang();
            }
            
            void eventinlet_22_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_03_in2_set(converted);
                }
            }
            
            void eventinlet_23_out1_bang_bang() {}
            
            void eventinlet_23_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->dspexpr_04_in2_set(converted);
                }
            }
            
            void eventinlet_24_out1_bang_bang() {
                this->codebox_08_in2_bang();
                this->codebox_06_in2_bang();
            }
            
            void eventinlet_24_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->codebox_08_in2_set(converted);
                }
            
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->codebox_06_in2_set(converted);
                }
            }
            
            void numberobj_04_valin_set(number v) {
                this->numberobj_04_value_set(v);
            }
            
            void numberobj_04_format_set(number v) {
                this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {
                this->numberobj_04_init();
                this->p_02->initializeObjects();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->p_02->startup();
            }
            
            void allocateDataRefs() {
                this->p_02->allocateDataRefs();
                this->cycle_tilde_02_buffer->requestSize(16384, 1);
                this->cycle_tilde_02_buffer->setSampleRate(this->sr);
                this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();
            }
            
            void selector_03_onoff_set(number v) {
                this->selector_03_onoff = v;
            }
            
            void eventinlet_21_out1_number_set(number v) {
                this->selector_03_onoff_set(v);
            }
            
            void expr_03_in2_set(number v) {
                this->expr_03_in2 = v;
            }
            
            void eventinlet_22_out1_number_set(number v) {
                this->expr_03_in2_set(v);
            }
            
            void codebox_08_in2_set(number v) {
                this->codebox_08_in2 = v;
            }
            
            void codebox_06_in2_set(number v) {
                this->codebox_06_in2 = v;
            }
            
            void eventinlet_24_out1_number_set(number v) {
                this->codebox_08_in2_set(v);
                this->codebox_06_in2_set(v);
            }
            
            void dspexpr_04_in2_set(number v) {
                this->dspexpr_04_in2 = v;
            }
            
            void eventinlet_23_out1_number_set(number v) {
                this->dspexpr_04_in2_set(v);
            }
            
            void midiparse_03_channel_set(number ) {}
            
            void unpack_03_out2_set(number v) {
                this->unpack_03_out2 = v;
            }
            
            void saw_tilde_02_frequency_set(number v) {
                this->saw_tilde_02_frequency = v;
            }
            
            void rect_tilde_02_frequency_set(number v) {
                this->rect_tilde_02_frequency = v;
            }
            
            void tri_tilde_02_frequency_set(number v) {
                this->tri_tilde_02_frequency = v;
            }
            
            void cycle_tilde_02_frequency_set(number v) {
                this->cycle_tilde_02_frequency = v;
            }
            
            void p_02_out1_number_set(number v) {
                this->saw_tilde_02_frequency_set(v);
                this->rect_tilde_02_frequency_set(v);
                this->tri_tilde_02_frequency_set(v);
                this->cycle_tilde_02_frequency_set(v);
            }
            
            void p_02_in3_number_set(number v) {
                this->p_02->updateTime(this->_currentTime);
                this->p_02->eventinlet_18_out1_number_set(v);
            }
            
            void codebox_08_out1_set(number v) {
                this->codebox_08_out1 = v;
                this->p_02_in3_number_set(this->codebox_08_out1);
            }
            
            void codebox_08_in1_set(number in1) {
                this->codebox_08_in1 = in1;
            
                list freqs = {
                    16.351625,
                    17.22640329,
                    17.44173333,
                    18.16847222,
                    18.39557813,
                    19.3797037,
                    19.62195,
                    20.43953125,
                    20.69502539,
                    21.80216667,
                    22.07469375,
                    22.99447266,
                    23.28190356,
                    24.5274375,
                    25.83960494,
                    26.1626,
                    27.25270833,
                    27.59336719,
                    29.06955556,
                    29.432925,
                    30.65929688,
                    31.04253809,
                    32.70325,
                    34.45280658,
                    34.88346667,
                    36.33694444,
                    36.79115625,
                    38.75940741,
                    39.2439,
                    40.8790625,
                    41.39005078,
                    43.60433333,
                    44.1493875,
                    45.98894531,
                    46.56380713,
                    49.054875,
                    51.67920988,
                    52.3252,
                    54.50541667,
                    55.18673438,
                    58.13911111,
                    58.86585,
                    61.31859375,
                    62.08507617,
                    65.4065,
                    68.90561317,
                    69.76693333,
                    72.67388889,
                    73.5823125,
                    77.51881481,
                    78.4878,
                    81.758125,
                    82.78010156,
                    87.20866667,
                    88.298775,
                    91.97789063,
                    93.12761426,
                    98.10975,
                    103.3584198,
                    104.6504,
                    109.0108333,
                    110.3734688,
                    116.2782222,
                    117.7317,
                    122.6371875,
                    124.1701523,
                    130.813,
                    137.8112263,
                    139.5338667,
                    145.3477778,
                    147.164625,
                    155.0376296,
                    156.9756,
                    163.51625,
                    165.5602031,
                    174.4173333,
                    176.59755,
                    183.9557813,
                    186.2552285,
                    196.2195,
                    206.7168395,
                    209.3008,
                    218.0216667,
                    220.7469375,
                    232.5564444,
                    235.4634,
                    245.274375,
                    248.3403047,
                    261.626,
                    275.6224527,
                    279.0677333,
                    290.6955556,
                    294.32925,
                    310.0752593,
                    313.9512,
                    327.0325,
                    331.1204063,
                    348.8346667,
                    353.1951,
                    367.9115625,
                    372.510457,
                    392.439,
                    413.433679,
                    418.6016,
                    436.0433333,
                    441.493875,
                    465.1128889,
                    470.9268,
                    490.54875,
                    496.6806094,
                    523.252,
                    551.2449053,
                    558.1354667,
                    581.3911111,
                    588.6585,
                    620.1505185,
                    627.9024,
                    654.065,
                    662.2408125,
                    697.6693333,
                    706.3902,
                    735.823125,
                    745.0209141,
                    784.878,
                    826.867358,
                    837.2032,
                    872.0866667,
                    882.98775,
                    930.2257778,
                    941.8536,
                    981.0975,
                    993.3612188,
                    1046.504,
                    1102.489811,
                    1116.270933,
                    1162.782222,
                    1177.317,
                    1240.301037,
                    1255.8048,
                    1308.13,
                    1324.481625,
                    1395.338667,
                    1412.7804,
                    1471.64625,
                    1490.041828,
                    1569.756,
                    1653.734716,
                    1674.4064,
                    1744.173333,
                    1765.9755,
                    1860.451556,
                    1883.7072,
                    1962.195,
                    1986.722438,
                    2093.008,
                    2204.979621,
                    2232.541867,
                    2325.564444,
                    2354.634,
                    2480.602074,
                    2511.6096,
                    2616.26,
                    2648.96325,
                    2790.677333,
                    2825.5608,
                    2943.2925,
                    2980.083656,
                    3139.512,
                    3307.469432,
                    3348.8128,
                    3488.346667,
                    3531.951,
                    3720.903111,
                    3767.4144,
                    3924.39,
                    3973.444875,
                    4186.016,
                    4409.959243,
                    4465.083733,
                    4651.128889,
                    4709.268,
                    4961.204148,
                    5023.2192,
                    5232.52,
                    5297.9265,
                    5581.354667,
                    5651.1216,
                    5886.585,
                    5960.167313,
                    6279.024,
                    6614.938864,
                    6697.6256,
                    6976.693333,
                    7063.902,
                    7441.806222,
                    7534.8288,
                    7848.78,
                    7946.88975,
                    8372.032,
                    8819.918486,
                    8930.167467,
                    9302.257778,
                    9418.536,
                    9922.408296,
                    10046.4384,
                    10465.04,
                    10595.853,
                    11162.70933,
                    11302.2432,
                    11773.17,
                    11920.33463,
                    12558.048,
                    13229.87773,
                    13395.2512,
                    13953.38667,
                    14127.804,
                    14883.61244,
                    15069.6576,
                    15697.56,
                    15893.7795,
                    16744.064,
                    17639.83697,
                    17860.33493,
                    18604.51556,
                    18837.072,
                    19844.81659,
                    20092.8768,
                    20930.08,
                    21191.706,
                    22325.41867,
                    22604.4864,
                    23546.34,
                    23840.66925,
                    25116.096,
                    26459.75546,
                    26790.5024,
                    27906.77333,
                    28255.608,
                    29767.22489,
                    30139.3152,
                    31395.12,
                    31787.559,
                    33488.128,
                    35279.67394,
                    35720.66987,
                    37209.03111,
                    37674.144,
                    39689.63319,
                    40185.7536,
                    41860.16,
                    42383.412,
                    44650.83733,
                    45208.9728,
                    47092.68,
                    47681.3385,
                    50232.192,
                    52919.51091,
                    53581.0048,
                    55813.54667,
                    56511.216,
                    59534.44978,
                    60278.6304,
                    62790.24,
                    63575.118
                };
            
                number midiNum = this->codebox_08_in1;
                number freq = freqs[(Index)(midiNum + this->codebox_08_in2)];
                this->codebox_08_out1_set(freq);//#map:OscillatorII/codebox_obj-26:4
            }
            
            void p_02_in2_number_set(number v) {
                this->p_02->updateTime(this->_currentTime);
                this->p_02->eventinlet_17_out1_number_set(v);
            }
            
            void codebox_07_out1_set(number v) {
                this->codebox_07_out1 = v;
                this->p_02_in2_number_set(this->codebox_07_out1);
            }
            
            void codebox_07_in1_set(number in1) {
                this->codebox_07_in1 = in1;
            
                list freqs = {
                    16.351625,
                    17.22640329,
                    17.44173333,
                    18.16847222,
                    18.39557813,
                    19.3797037,
                    19.62195,
                    20.43953125,
                    20.69502539,
                    21.80216667,
                    22.07469375,
                    22.99447266,
                    23.28190356,
                    24.5274375,
                    25.83960494,
                    26.1626,
                    27.25270833,
                    27.59336719,
                    29.06955556,
                    29.432925,
                    30.65929688,
                    31.04253809,
                    32.70325,
                    34.45280658,
                    34.88346667,
                    36.33694444,
                    36.79115625,
                    38.75940741,
                    39.2439,
                    40.8790625,
                    41.39005078,
                    43.60433333,
                    44.1493875,
                    45.98894531,
                    46.56380713,
                    49.054875,
                    51.67920988,
                    52.3252,
                    54.50541667,
                    55.18673438,
                    58.13911111,
                    58.86585,
                    61.31859375,
                    62.08507617,
                    65.4065,
                    68.90561317,
                    69.76693333,
                    72.67388889,
                    73.5823125,
                    77.51881481,
                    78.4878,
                    81.758125,
                    82.78010156,
                    87.20866667,
                    88.298775,
                    91.97789063,
                    93.12761426,
                    98.10975,
                    103.3584198,
                    104.6504,
                    109.0108333,
                    110.3734688,
                    116.2782222,
                    117.7317,
                    122.6371875,
                    124.1701523,
                    130.813,
                    137.8112263,
                    139.5338667,
                    145.3477778,
                    147.164625,
                    155.0376296,
                    156.9756,
                    163.51625,
                    165.5602031,
                    174.4173333,
                    176.59755,
                    183.9557813,
                    186.2552285,
                    196.2195,
                    206.7168395,
                    209.3008,
                    218.0216667,
                    220.7469375,
                    232.5564444,
                    235.4634,
                    245.274375,
                    248.3403047,
                    261.626,
                    275.6224527,
                    279.0677333,
                    290.6955556,
                    294.32925,
                    310.0752593,
                    313.9512,
                    327.0325,
                    331.1204063,
                    348.8346667,
                    353.1951,
                    367.9115625,
                    372.510457,
                    392.439,
                    413.433679,
                    418.6016,
                    436.0433333,
                    441.493875,
                    465.1128889,
                    470.9268,
                    490.54875,
                    496.6806094,
                    523.252,
                    551.2449053,
                    558.1354667,
                    581.3911111,
                    588.6585,
                    620.1505185,
                    627.9024,
                    654.065,
                    662.2408125,
                    697.6693333,
                    706.3902,
                    735.823125,
                    745.0209141,
                    784.878,
                    826.867358,
                    837.2032,
                    872.0866667,
                    882.98775,
                    930.2257778,
                    941.8536,
                    981.0975,
                    993.3612188,
                    1046.504,
                    1102.489811,
                    1116.270933,
                    1162.782222,
                    1177.317,
                    1240.301037,
                    1255.8048,
                    1308.13,
                    1324.481625,
                    1395.338667,
                    1412.7804,
                    1471.64625,
                    1490.041828,
                    1569.756,
                    1653.734716,
                    1674.4064,
                    1744.173333,
                    1765.9755,
                    1860.451556,
                    1883.7072,
                    1962.195,
                    1986.722438,
                    2093.008,
                    2204.979621,
                    2232.541867,
                    2325.564444,
                    2354.634,
                    2480.602074,
                    2511.6096,
                    2616.26,
                    2648.96325,
                    2790.677333,
                    2825.5608,
                    2943.2925,
                    2980.083656,
                    3139.512,
                    3307.469432,
                    3348.8128,
                    3488.346667,
                    3531.951,
                    3720.903111,
                    3767.4144,
                    3924.39,
                    3973.444875,
                    4186.016,
                    4409.959243,
                    4465.083733,
                    4651.128889,
                    4709.268,
                    4961.204148,
                    5023.2192,
                    5232.52,
                    5297.9265,
                    5581.354667,
                    5651.1216,
                    5886.585,
                    5960.167313,
                    6279.024,
                    6614.938864,
                    6697.6256,
                    6976.693333,
                    7063.902,
                    7441.806222,
                    7534.8288,
                    7848.78,
                    7946.88975,
                    8372.032,
                    8819.918486,
                    8930.167467,
                    9302.257778,
                    9418.536,
                    9922.408296,
                    10046.4384,
                    10465.04,
                    10595.853,
                    11162.70933,
                    11302.2432,
                    11773.17,
                    11920.33463,
                    12558.048,
                    13229.87773,
                    13395.2512,
                    13953.38667,
                    14127.804,
                    14883.61244,
                    15069.6576,
                    15697.56,
                    15893.7795,
                    16744.064,
                    17639.83697,
                    17860.33493,
                    18604.51556,
                    18837.072,
                    19844.81659,
                    20092.8768,
                    20930.08,
                    21191.706,
                    22325.41867,
                    22604.4864,
                    23546.34,
                    23840.66925,
                    25116.096,
                    26459.75546,
                    26790.5024,
                    27906.77333,
                    28255.608,
                    29767.22489,
                    30139.3152,
                    31395.12,
                    31787.559,
                    33488.128,
                    35279.67394,
                    35720.66987,
                    37209.03111,
                    37674.144,
                    39689.63319,
                    40185.7536,
                    41860.16,
                    42383.412,
                    44650.83733,
                    45208.9728,
                    47092.68,
                    47681.3385,
                    50232.192,
                    52919.51091,
                    53581.0048,
                    55813.54667,
                    56511.216,
                    59534.44978,
                    60278.6304,
                    62790.24,
                    63575.118
                };
            
                number midiNum = this->codebox_07_in1;
                number freq = freqs[(Index)midiNum];
                this->codebox_07_out1_set(freq);//#map:OscillatorII/codebox_obj-25:4
            }
            
            void p_02_in1_number_set(number v) {
                this->p_02->updateTime(this->_currentTime);
                this->p_02->eventinlet_16_out1_number_set(v);
            }
            
            void codebox_06_out1_set(number v) {
                this->codebox_06_out1 = v;
                this->p_02_in1_number_set(this->codebox_06_out1);
            }
            
            void codebox_06_in1_set(number in1) {
                this->codebox_06_in1 = in1;
            
                list freqs = {
                    16.351625,
                    17.22640329,
                    17.44173333,
                    18.16847222,
                    18.39557813,
                    19.3797037,
                    19.62195,
                    20.43953125,
                    20.69502539,
                    21.80216667,
                    22.07469375,
                    22.99447266,
                    23.28190356,
                    24.5274375,
                    25.83960494,
                    26.1626,
                    27.25270833,
                    27.59336719,
                    29.06955556,
                    29.432925,
                    30.65929688,
                    31.04253809,
                    32.70325,
                    34.45280658,
                    34.88346667,
                    36.33694444,
                    36.79115625,
                    38.75940741,
                    39.2439,
                    40.8790625,
                    41.39005078,
                    43.60433333,
                    44.1493875,
                    45.98894531,
                    46.56380713,
                    49.054875,
                    51.67920988,
                    52.3252,
                    54.50541667,
                    55.18673438,
                    58.13911111,
                    58.86585,
                    61.31859375,
                    62.08507617,
                    65.4065,
                    68.90561317,
                    69.76693333,
                    72.67388889,
                    73.5823125,
                    77.51881481,
                    78.4878,
                    81.758125,
                    82.78010156,
                    87.20866667,
                    88.298775,
                    91.97789063,
                    93.12761426,
                    98.10975,
                    103.3584198,
                    104.6504,
                    109.0108333,
                    110.3734688,
                    116.2782222,
                    117.7317,
                    122.6371875,
                    124.1701523,
                    130.813,
                    137.8112263,
                    139.5338667,
                    145.3477778,
                    147.164625,
                    155.0376296,
                    156.9756,
                    163.51625,
                    165.5602031,
                    174.4173333,
                    176.59755,
                    183.9557813,
                    186.2552285,
                    196.2195,
                    206.7168395,
                    209.3008,
                    218.0216667,
                    220.7469375,
                    232.5564444,
                    235.4634,
                    245.274375,
                    248.3403047,
                    261.626,
                    275.6224527,
                    279.0677333,
                    290.6955556,
                    294.32925,
                    310.0752593,
                    313.9512,
                    327.0325,
                    331.1204063,
                    348.8346667,
                    353.1951,
                    367.9115625,
                    372.510457,
                    392.439,
                    413.433679,
                    418.6016,
                    436.0433333,
                    441.493875,
                    465.1128889,
                    470.9268,
                    490.54875,
                    496.6806094,
                    523.252,
                    551.2449053,
                    558.1354667,
                    581.3911111,
                    588.6585,
                    620.1505185,
                    627.9024,
                    654.065,
                    662.2408125,
                    697.6693333,
                    706.3902,
                    735.823125,
                    745.0209141,
                    784.878,
                    826.867358,
                    837.2032,
                    872.0866667,
                    882.98775,
                    930.2257778,
                    941.8536,
                    981.0975,
                    993.3612188,
                    1046.504,
                    1102.489811,
                    1116.270933,
                    1162.782222,
                    1177.317,
                    1240.301037,
                    1255.8048,
                    1308.13,
                    1324.481625,
                    1395.338667,
                    1412.7804,
                    1471.64625,
                    1490.041828,
                    1569.756,
                    1653.734716,
                    1674.4064,
                    1744.173333,
                    1765.9755,
                    1860.451556,
                    1883.7072,
                    1962.195,
                    1986.722438,
                    2093.008,
                    2204.979621,
                    2232.541867,
                    2325.564444,
                    2354.634,
                    2480.602074,
                    2511.6096,
                    2616.26,
                    2648.96325,
                    2790.677333,
                    2825.5608,
                    2943.2925,
                    2980.083656,
                    3139.512,
                    3307.469432,
                    3348.8128,
                    3488.346667,
                    3531.951,
                    3720.903111,
                    3767.4144,
                    3924.39,
                    3973.444875,
                    4186.016,
                    4409.959243,
                    4465.083733,
                    4651.128889,
                    4709.268,
                    4961.204148,
                    5023.2192,
                    5232.52,
                    5297.9265,
                    5581.354667,
                    5651.1216,
                    5886.585,
                    5960.167313,
                    6279.024,
                    6614.938864,
                    6697.6256,
                    6976.693333,
                    7063.902,
                    7441.806222,
                    7534.8288,
                    7848.78,
                    7946.88975,
                    8372.032,
                    8819.918486,
                    8930.167467,
                    9302.257778,
                    9418.536,
                    9922.408296,
                    10046.4384,
                    10465.04,
                    10595.853,
                    11162.70933,
                    11302.2432,
                    11773.17,
                    11920.33463,
                    12558.048,
                    13229.87773,
                    13395.2512,
                    13953.38667,
                    14127.804,
                    14883.61244,
                    15069.6576,
                    15697.56,
                    15893.7795,
                    16744.064,
                    17639.83697,
                    17860.33493,
                    18604.51556,
                    18837.072,
                    19844.81659,
                    20092.8768,
                    20930.08,
                    21191.706,
                    22325.41867,
                    22604.4864,
                    23546.34,
                    23840.66925,
                    25116.096,
                    26459.75546,
                    26790.5024,
                    27906.77333,
                    28255.608,
                    29767.22489,
                    30139.3152,
                    31395.12,
                    31787.559,
                    33488.128,
                    35279.67394,
                    35720.66987,
                    37209.03111,
                    37674.144,
                    39689.63319,
                    40185.7536,
                    41860.16,
                    42383.412,
                    44650.83733,
                    45208.9728,
                    47092.68,
                    47681.3385,
                    50232.192,
                    52919.51091,
                    53581.0048,
                    55813.54667,
                    56511.216,
                    59534.44978,
                    60278.6304,
                    62790.24,
                    63575.118
                };
            
                number midiNum = this->codebox_06_in1;
                number freq = freqs[(Index)(midiNum - this->codebox_06_in2)];
                this->codebox_06_out1_set(freq);//#map:OscillatorII/codebox_obj-9:4
            }
            
            void expr_03_out1_set(number v) {
                this->expr_03_out1 = v;
                this->codebox_08_in1_set(this->expr_03_out1);
                this->codebox_07_in1_set(this->expr_03_out1);
                this->codebox_06_in1_set(this->expr_03_out1);
            }
            
            void expr_03_in1_set(number in1) {
                this->expr_03_in1 = in1;
                this->expr_03_out1_set(this->expr_03_in1 + this->expr_03_in2);//#map:OscillatorII/+_obj-10:1
            }
            
            void unpack_03_out1_set(number v) {
                this->unpack_03_out1 = v;
                this->expr_03_in1_set(v);
            }
            
            void unpack_03_input_list_set(const list& v) {
                if (v->length > 1)
                    this->unpack_03_out2_set(trunc(v[1]));
            
                if (v->length > 0)
                    this->unpack_03_out1_set(trunc(v[0]));
            }
            
            void midiparse_03_noteonoroff_set(const list& v) {
                this->unpack_03_input_list_set(v);
            }
            
            void midiparse_03_polypressure_set(const list& ) {}
            
            void midiparse_03_controlchange_set(const list& ) {}
            
            void midiparse_03_programchange_set(number ) {}
            
            void midiparse_03_aftertouch_set(number ) {}
            
            void p_02_in4_number_set(number v) {
                this->p_02->updateTime(this->_currentTime);
                this->p_02->eventinlet_19_out1_number_set(v);
            }
            
            void numberobj_04_output_set(number v) {
                this->p_02_in4_number_set(v);
            }
            
            void numberobj_04_value_set(number v) {
                this->numberobj_04_value_setter(v);
                v = this->numberobj_04_value;
                number localvalue = v;
            
                if (this->numberobj_04_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("poly/OscillatorII/number_obj-24"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_04_output_set(localvalue);
            }
            
            void midiparse_03_pitchbend_set(number v) {
                this->numberobj_04_value_set(v);
            }
            
            void midiparse_03_midiin_set(number midivalue) {
                list result = this->midiparse_03_parser_next(midivalue);
            
                switch ((int)result[0]) {
                case 0:
                    {
                    this->midiparse_03_channel_set(result[3]);
                    this->midiparse_03_noteonoroff_set({result[1], result[2]});
                    break;
                    }
                case 1:
                    {
                    this->midiparse_03_channel_set(result[3]);
                    this->midiparse_03_polypressure_set({result[1], result[2]});
                    break;
                    }
                case 2:
                    {
                    this->midiparse_03_channel_set(result[3]);
                    this->midiparse_03_controlchange_set({result[1], result[2]});
                    break;
                    }
                case 3:
                    {
                    this->midiparse_03_channel_set(result[2]);
                    this->midiparse_03_programchange_set(result[1]);
                    break;
                    }
                case 4:
                    {
                    this->midiparse_03_channel_set(result[2]);
                    this->midiparse_03_aftertouch_set(result[1]);
                    break;
                    }
                case 5:
                    {
                    this->midiparse_03_channel_set(result[2]);
                    this->midiparse_03_pitchbend_set(result[1]);
                    break;
                    }
                }
            }
            
            void eventinlet_20_out1_number_set(number v) {
                this->midiparse_03_midiin_set(v);
            }
            
            void expr_03_in2_bang() {}
            
            void codebox_08_in2_bang() {}
            
            void codebox_06_in2_bang() {}
            
            void p_02_perform(Index n) {
                // subpatcher: BendFreq
                this->p_02->process(nullptr, 0, nullptr, 0, n);
            }
            
            void cycle_tilde_02_perform(
                number frequency,
                number phase_offset,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(phase_offset);
                auto __cycle_tilde_02_f2i = this->cycle_tilde_02_f2i;
                auto __cycle_tilde_02_buffer = this->cycle_tilde_02_buffer;
                auto __cycle_tilde_02_phasei = this->cycle_tilde_02_phasei;
                Index i;
            
                for (i = 0; i < n; i++) {
                    {
                        uint32_t uint_phase;
            
                        {
                            {
                                uint_phase = __cycle_tilde_02_phasei;
                            }
                        }
            
                        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
                        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                        number y0 = __cycle_tilde_02_buffer[(Index)idx];
                        number y1 = __cycle_tilde_02_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                        number y = y0 + frac * (y1 - y0);
            
                        {
                            uint32_t pincr = (uint32_t)(uint32_trunc(frequency * __cycle_tilde_02_f2i));
                            __cycle_tilde_02_phasei = uint32_add(__cycle_tilde_02_phasei, pincr);
                        }
            
                        out1[(Index)i] = y;
                        out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                        continue;
                    }
                }
            
                this->cycle_tilde_02_phasei = __cycle_tilde_02_phasei;
            }
            
            void tri_tilde_02_perform(
                number frequency,
                number pulsewidth,
                number syncPhase,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(syncPhase);
                RNBO_UNUSED(pulsewidth);
                auto __tri_tilde_02_yn3 = this->tri_tilde_02_yn3;
                auto __tri_tilde_02_yn2 = this->tri_tilde_02_yn2;
                auto __tri_tilde_02_yn1 = this->tri_tilde_02_yn1;
                auto __tri_tilde_02_app_correction = this->tri_tilde_02_app_correction;
                auto __tri_tilde_02_flg = this->tri_tilde_02_flg;
                auto __tri_tilde_02_yn = this->tri_tilde_02_yn;
                auto __tri_tilde_02_t = this->tri_tilde_02_t;
                auto __tri_tilde_02_lastSyncDiff = this->tri_tilde_02_lastSyncDiff;
                auto __tri_tilde_02_lastSyncPhase = this->tri_tilde_02_lastSyncPhase;
                Index i;
            
                for (i = 0; i < n; i++) {
                    number __frequency = frequency;
                    __frequency = rnbo_abs(__frequency);
                    number dt = __frequency / this->samplerate();
            
                    if (dt != 0.0) {
                        number pw = 0.5;
                        {}
                        number syncDiff = 0 - __tri_tilde_02_lastSyncPhase;
                        __tri_tilde_02_lastSyncPhase = 0;
                        __tri_tilde_02_lastSyncDiff = syncDiff;
                        number syncLookahead = 0 + syncDiff;
            
                        if (syncLookahead > 1) {
                            __tri_tilde_02_t = 0;
                        }
            
                        number tCurr = __tri_tilde_02_t;
                        number upSlope = __frequency / (pw * this->samplerate());
                        number downSlope = __frequency / ((1 - pw) * this->samplerate());
            
                        if (tCurr <= pw) {
                            __tri_tilde_02_yn = (number)2 / pw * tCurr - 1;
            
                            if (__tri_tilde_02_flg == -1) {
                                __tri_tilde_02_app_correction = 1;
                                __tri_tilde_02_flg = 1;
                            } else if (__tri_tilde_02_app_correction == 1) {
                                __tri_tilde_02_app_correction = 0;
                                number d = (tCurr - dt) / dt;
                                number d2 = d * d;
                                number d3 = d2 * d;
                                number d4 = d2 * d2;
                                number d5 = d * d4;
                                number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                number h3 = d5 / (number)120;
                                __tri_tilde_02_yn += upSlope * h0;
                                __tri_tilde_02_yn1 += upSlope * h1;
                                __tri_tilde_02_yn2 += upSlope * h2;
                                __tri_tilde_02_yn3 += upSlope * h3;
                            }
            
                            __tri_tilde_02_flg = 1;
                        } else {
                            __tri_tilde_02_yn = 1 - 2 * (tCurr - pw) / (1 - pw);
            
                            if (__tri_tilde_02_flg == 1) {
                                __tri_tilde_02_app_correction = 1;
                            } else if (__tri_tilde_02_app_correction == 1) {
                                __tri_tilde_02_app_correction = 0;
                                number d = (tCurr - pw - dt) / dt;
                                number d2 = d * d;
                                number d3 = d2 * d;
                                number d4 = d2 * d2;
                                number d5 = d4 * d;
                                number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                number h3 = d5 / (number)120;
                                __tri_tilde_02_yn -= downSlope * h0;
                                __tri_tilde_02_yn1 -= downSlope * h1;
                                __tri_tilde_02_yn2 -= downSlope * h2;
                                __tri_tilde_02_yn3 -= downSlope * h3;
                            }
            
                            __tri_tilde_02_flg = -1;
                        }
                    }
            
                    number y = __tri_tilde_02_yn3;
                    __tri_tilde_02_yn3 = __tri_tilde_02_yn2;
                    __tri_tilde_02_yn2 = __tri_tilde_02_yn1;
                    __tri_tilde_02_yn1 = __tri_tilde_02_yn;
                    __tri_tilde_02_t += dt;
            
                    if (dt > 0) {
                        while (__tri_tilde_02_t >= 1) {
                            __tri_tilde_02_t -= 1;
                        }
                    } else {
                        while (__tri_tilde_02_t <= 0) {
                            __tri_tilde_02_t += 1;
                        }
                    }
            
                    y = this->tri_tilde_02_dcblocker_next(y, 0.9997);
                    out1[(Index)i] = y * 0.5;
                    out2[(Index)i] = __tri_tilde_02_t;
                }
            
                this->tri_tilde_02_lastSyncPhase = __tri_tilde_02_lastSyncPhase;
                this->tri_tilde_02_lastSyncDiff = __tri_tilde_02_lastSyncDiff;
                this->tri_tilde_02_t = __tri_tilde_02_t;
                this->tri_tilde_02_yn = __tri_tilde_02_yn;
                this->tri_tilde_02_flg = __tri_tilde_02_flg;
                this->tri_tilde_02_app_correction = __tri_tilde_02_app_correction;
                this->tri_tilde_02_yn1 = __tri_tilde_02_yn1;
                this->tri_tilde_02_yn2 = __tri_tilde_02_yn2;
                this->tri_tilde_02_yn3 = __tri_tilde_02_yn3;
            }
            
            void rect_tilde_02_perform(
                number frequency,
                number pulsewidth,
                number syncPhase,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(syncPhase);
                RNBO_UNUSED(pulsewidth);
                auto __rect_tilde_02_xHistory = this->rect_tilde_02_xHistory;
                auto __rect_tilde_02_yHistory = this->rect_tilde_02_yHistory;
                auto __rect_tilde_02_didSync = this->rect_tilde_02_didSync;
                auto __rect_tilde_02_t = this->rect_tilde_02_t;
                auto __rect_tilde_02_lastSyncDiff = this->rect_tilde_02_lastSyncDiff;
                auto __rect_tilde_02_lastSyncPhase = this->rect_tilde_02_lastSyncPhase;
                Index i;
            
                for (i = 0; i < n; i++) {
                    number __frequency = frequency;
                    __frequency = rnbo_abs(__frequency);
                    number dt = __frequency / this->samplerate();
                    number pw = 0.5;
                    number syncDiff = 0 - __rect_tilde_02_lastSyncPhase;
                    __rect_tilde_02_lastSyncPhase = 0;
                    __rect_tilde_02_lastSyncDiff = syncDiff;
                    number syncLookahead = 0 + syncDiff;
                    number tCurr = __rect_tilde_02_t;
                    number tPrev = tCurr - dt;
                    number tNext = tCurr + dt;
            
                    if (tPrev < 0) {
                        while (tPrev < 0) {
                            tPrev += 1;
                        }
                    }
            
                    if (tNext > 1) {
                        while (tNext >= 1) {
                            tNext -= 1;
                        }
                    }
            
                    number yNext = this->rect_tilde_02_rectangle(tNext, pw);
                    number yCurr = this->rect_tilde_02_rectangle(tCurr, pw);
                    number yPrev = this->rect_tilde_02_rectangle(tPrev, pw);
            
                    if (dt != 0.0) {
                        if (yPrev < yCurr) {
                            number d = tCurr / dt;
                            yCurr += d - 0.5 * d * d - 0.5;
                        } else if (yCurr < yNext) {
                            number d = (1 - tCurr) / dt;
                            yCurr += 0.5 * d * d + d + 0.5;
                        } else if (yPrev > yCurr) {
                            number d = (tCurr - pw) / dt;
                            yCurr -= d - 0.5 * d * d - 0.5;
                        } else if (yCurr > yNext) {
                            number d = (pw - tCurr) / dt;
                            yCurr -= 0.5 * d * d + d + 0.5;
                        } else if ((bool)(__rect_tilde_02_didSync)) {
                            yCurr = 0.25;
                            __rect_tilde_02_didSync = false;
                        } else if (syncLookahead > 1) {
                            if (yCurr < 0) {
                                yCurr = -0.125;
                            }
            
                            __rect_tilde_02_t = 0;
                            __rect_tilde_02_didSync = true;
                        }
            
                        __rect_tilde_02_t += dt;
            
                        if (dt > 0) {
                            while (__rect_tilde_02_t >= 1) {
                                __rect_tilde_02_t -= 1;
                            }
                        } else {
                            while (__rect_tilde_02_t <= 0) {
                                __rect_tilde_02_t += 1;
                            }
                        }
                    }
            
                    number output = yCurr - __rect_tilde_02_yHistory + __rect_tilde_02_xHistory * 0.9997;
                    __rect_tilde_02_xHistory = output;
                    __rect_tilde_02_yHistory = yCurr;
                    out1[(Index)i] = 0.5 * output;
                    out2[(Index)i] = __rect_tilde_02_t;
                }
            
                this->rect_tilde_02_lastSyncPhase = __rect_tilde_02_lastSyncPhase;
                this->rect_tilde_02_lastSyncDiff = __rect_tilde_02_lastSyncDiff;
                this->rect_tilde_02_t = __rect_tilde_02_t;
                this->rect_tilde_02_didSync = __rect_tilde_02_didSync;
                this->rect_tilde_02_yHistory = __rect_tilde_02_yHistory;
                this->rect_tilde_02_xHistory = __rect_tilde_02_xHistory;
            }
            
            void saw_tilde_02_perform(
                number frequency,
                number syncPhase,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(syncPhase);
                auto __saw_tilde_02_didSync = this->saw_tilde_02_didSync;
                auto __saw_tilde_02_lastSyncDiff = this->saw_tilde_02_lastSyncDiff;
                auto __saw_tilde_02_lastSyncPhase = this->saw_tilde_02_lastSyncPhase;
                auto __saw_tilde_02_t = this->saw_tilde_02_t;
                Index i;
            
                for (i = 0; i < n; i++) {
                    number dt = frequency / this->samplerate();
                    number t1 = __saw_tilde_02_t + 0.5;
                    t1 -= trunc(t1);
                    number y = 2 * t1 - 1;
            
                    if (dt != 0.0) {
                        number syncDiff = 0 - __saw_tilde_02_lastSyncPhase;
                        __saw_tilde_02_lastSyncPhase = 0;
                        __saw_tilde_02_lastSyncDiff = syncDiff;
                        number lookahead = 0 + syncDiff;
            
                        if (t1 < dt) {
                            number d = t1 / dt;
                            y -= d + d - d * d - 1;
                        } else if (t1 + dt > 1) {
                            number d = (t1 - 1) / dt;
                            y -= d + d + d * d + 1;
                        } else if ((bool)(__saw_tilde_02_didSync)) {
                            y = 0;
                            __saw_tilde_02_didSync = false;
                        } else if (lookahead > 1) {
                            y *= 0.5;
                            __saw_tilde_02_t = 0;
                            __saw_tilde_02_didSync = true;
                        }
            
                        __saw_tilde_02_t += dt;
            
                        if (dt > 0) {
                            while (__saw_tilde_02_t >= 1) {
                                __saw_tilde_02_t -= 1;
                            }
                        } else {
                            while (__saw_tilde_02_t <= 0) {
                                __saw_tilde_02_t += 1;
                            }
                        }
                    }
            
                    y = this->saw_tilde_02_dcblocker_next(y, 0.9997);
                    out1[(Index)i] = 0.5 * y;
                    out2[(Index)i] = __saw_tilde_02_t;
                }
            
                this->saw_tilde_02_t = __saw_tilde_02_t;
                this->saw_tilde_02_lastSyncPhase = __saw_tilde_02_lastSyncPhase;
                this->saw_tilde_02_lastSyncDiff = __saw_tilde_02_lastSyncDiff;
                this->saw_tilde_02_didSync = __saw_tilde_02_didSync;
            }
            
            void selector_03_perform(
                number onoff,
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                const SampleValue * in4,
                SampleValue * out,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (onoff >= 1 && onoff < 2)
                        out[(Index)i] = in1[(Index)i];
                    else if (onoff >= 2 && onoff < 3)
                        out[(Index)i] = in2[(Index)i];
                    else if (onoff >= 3 && onoff < 4)
                        out[(Index)i] = in3[(Index)i];
                    else if (onoff >= 4 && onoff < 5)
                        out[(Index)i] = in4[(Index)i];
                    else
                        out[(Index)i] = 0;
                }
            }
            
            void dspexpr_04_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void numberobj_04_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_04_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_04_value = localvalue;
            }
            
            number cycle_tilde_02_ph_next(number freq, number reset) {
                {
                    {
                        if (reset >= 0.)
                            this->cycle_tilde_02_ph_currentPhase = reset;
                    }
                }
            
                number pincr = freq * this->cycle_tilde_02_ph_conv;
            
                if (this->cycle_tilde_02_ph_currentPhase < 0.)
                    this->cycle_tilde_02_ph_currentPhase = 1. + this->cycle_tilde_02_ph_currentPhase;
            
                if (this->cycle_tilde_02_ph_currentPhase > 1.)
                    this->cycle_tilde_02_ph_currentPhase = this->cycle_tilde_02_ph_currentPhase - 1.;
            
                number tmp = this->cycle_tilde_02_ph_currentPhase;
                this->cycle_tilde_02_ph_currentPhase += pincr;
                return tmp;
            }
            
            void cycle_tilde_02_ph_reset() {
                this->cycle_tilde_02_ph_currentPhase = 0;
            }
            
            void cycle_tilde_02_ph_dspsetup() {
                this->cycle_tilde_02_ph_conv = (number)1 / this->sr;
            }
            
            void cycle_tilde_02_dspsetup(bool force) {
                if ((bool)(this->cycle_tilde_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->cycle_tilde_02_phasei = 0;
                this->cycle_tilde_02_f2i = (number)4294967296 / this->samplerate();
                this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
                this->cycle_tilde_02_setupDone = true;
                this->cycle_tilde_02_ph_dspsetup();
            }
            
            void cycle_tilde_02_bufferUpdated() {
                this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
            }
            
            list midiparse_03_parser_next(number midiin) {
                int midivalue = (int)(trunc(midiin));
                list result = list(-1);
                number resetByte1 = false;
            
                if (midivalue > 127) {
                    this->midiparse_03_parser_status = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0xFF);
                    this->midiparse_03_parser_byte1 = -1;
                } else {
                    switch ((int)((BinOpInt)this->midiparse_03_parser_status & (BinOpInt)0xF0)) {
                    case 0xB0:
                        {
                        if (this->midiparse_03_parser_byte1 == -1) {
                            this->midiparse_03_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                2,
                                this->midiparse_03_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_03_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xA0:
                        {
                        if (this->midiparse_03_parser_byte1 == -1) {
                            this->midiparse_03_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                1,
                                this->midiparse_03_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_03_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xE0:
                        {
                        if (this->midiparse_03_parser_byte1 == -1) {
                            this->midiparse_03_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            number pitchbend;
            
                            {
                                number val = this->midiparse_03_parser_byte1 + ((BinOpInt)(((BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32)));
            
                                {
                                    val -= 0x2000;
                                    pitchbend = val / (number)8192;
                                }
                            }
            
                            result = {
                                5,
                                pitchbend,
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_03_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xD0:
                        {
                        result = {
                            4,
                            (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                            (BinOpInt)((BinOpInt)(1 + this->midiparse_03_parser_status) & (BinOpInt)0x0F)
                        };
            
                        break;
                        }
                    case 0x90:
                        {
                        if (this->midiparse_03_parser_byte1 == -1) {
                            this->midiparse_03_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                0,
                                this->midiparse_03_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_03_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xC0:
                        {
                        result = {
                            3,
                            (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                            (BinOpInt)((BinOpInt)(1 + this->midiparse_03_parser_status) & (BinOpInt)0x0F)
                        };
            
                        break;
                        }
                    case 0x80:
                        {
                        if (this->midiparse_03_parser_byte1 == -1) {
                            this->midiparse_03_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                0,
                                this->midiparse_03_parser_byte1,
                                0,
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_03_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    default:
                        {
                        result = {-1};
                        }
                    }
                }
            
                if (result->length > 1) {
                    result->push(this->midiparse_03_parser_status);
                    result->push(this->midiparse_03_parser_byte1);
                    result->push(midivalue);
                }
            
                if ((bool)(resetByte1)) {
                    this->midiparse_03_parser_byte1 = -1;
                }
            
                return result;
            }
            
            void midiparse_03_parser_reset() {
                this->midiparse_03_parser_status = -1;
                this->midiparse_03_parser_byte1 = -1;
            }
            
            number tri_tilde_02_dcblocker_next(number x, number gain) {
                number y = x - this->tri_tilde_02_dcblocker_xm1 + this->tri_tilde_02_dcblocker_ym1 * gain;
                this->tri_tilde_02_dcblocker_xm1 = x;
                this->tri_tilde_02_dcblocker_ym1 = y;
                return y;
            }
            
            void tri_tilde_02_dcblocker_reset() {
                this->tri_tilde_02_dcblocker_xm1 = 0;
                this->tri_tilde_02_dcblocker_ym1 = 0;
            }
            
            void tri_tilde_02_dcblocker_dspsetup() {
                this->tri_tilde_02_dcblocker_reset();
            }
            
            void tri_tilde_02_dspsetup(bool force) {
                if ((bool)(this->tri_tilde_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->tri_tilde_02_setupDone = true;
                this->tri_tilde_02_dcblocker_dspsetup();
            }
            
            number rect_tilde_02_rectangle(number phase, number pulsewidth) {
                if (phase < pulsewidth) {
                    return 1;
                } else {
                    return -1;
                }
            }
            
            number saw_tilde_02_dcblocker_next(number x, number gain) {
                number y = x - this->saw_tilde_02_dcblocker_xm1 + this->saw_tilde_02_dcblocker_ym1 * gain;
                this->saw_tilde_02_dcblocker_xm1 = x;
                this->saw_tilde_02_dcblocker_ym1 = y;
                return y;
            }
            
            void saw_tilde_02_dcblocker_reset() {
                this->saw_tilde_02_dcblocker_xm1 = 0;
                this->saw_tilde_02_dcblocker_ym1 = 0;
            }
            
            void saw_tilde_02_dcblocker_dspsetup() {
                this->saw_tilde_02_dcblocker_reset();
            }
            
            void saw_tilde_02_dspsetup(bool force) {
                if ((bool)(this->saw_tilde_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->saw_tilde_02_setupDone = true;
                this->saw_tilde_02_dcblocker_dspsetup();
            }
            
            void numberobj_04_init() {
                this->numberobj_04_currentFormat = 6;
            
                this->getEngine()->sendNumMessage(
                    TAG("setup"),
                    TAG("poly/OscillatorII/number_obj-24"),
                    1,
                    this->_currentTime
                );
            }
            
            void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_04_value;
            }
            
            void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_04_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                p_02_target = 0;
                selector_03_onoff = 1;
                cycle_tilde_02_frequency = 0;
                cycle_tilde_02_phase_offset = 0;
                dspexpr_04_in1 = 0;
                dspexpr_04_in2 = 0;
                expr_03_in1 = 0;
                expr_03_in2 = 0;
                expr_03_out1 = 0;
                codebox_06_in1 = 0;
                codebox_06_in2 = 0;
                codebox_06_out1 = 0;
                unpack_03_out1 = 0;
                unpack_03_out2 = 0;
                tri_tilde_02_frequency = 0;
                tri_tilde_02_pulsewidth = 0.5;
                tri_tilde_02_syncPhase = 0;
                rect_tilde_02_frequency = 0;
                rect_tilde_02_pulsewidth = 0.5;
                rect_tilde_02_syncPhase = 0;
                saw_tilde_02_frequency = 0;
                saw_tilde_02_syncPhase = 0;
                codebox_07_in1 = 0;
                codebox_07_out1 = 0;
                codebox_08_in1 = 0;
                codebox_08_in2 = 0;
                codebox_08_out1 = 0;
                numberobj_04_value = 0;
                numberobj_04_value_setter(numberobj_04_value);
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                signals[3] = nullptr;
                signals[4] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                cycle_tilde_02_wrap = 0;
                cycle_tilde_02_ph_currentPhase = 0;
                cycle_tilde_02_ph_conv = 0;
                cycle_tilde_02_setupDone = false;
                midiparse_03_parser_status = -1;
                midiparse_03_parser_byte1 = -1;
                tri_tilde_02_t = 0;
                tri_tilde_02_lastSyncPhase = 0;
                tri_tilde_02_lastSyncDiff = 0;
                tri_tilde_02_didSync = false;
                tri_tilde_02_yn = 0;
                tri_tilde_02_yn1 = 0;
                tri_tilde_02_yn2 = 0;
                tri_tilde_02_yn3 = 0;
                tri_tilde_02_flg = 0;
                tri_tilde_02_app_correction = 0;
                tri_tilde_02_dcblocker_xm1 = 0;
                tri_tilde_02_dcblocker_ym1 = 0;
                tri_tilde_02_setupDone = false;
                rect_tilde_02_xHistory = 0;
                rect_tilde_02_yHistory = 0;
                rect_tilde_02_t = 0;
                rect_tilde_02_lastSyncPhase = 0;
                rect_tilde_02_lastSyncDiff = 0;
                rect_tilde_02_didSync = false;
                saw_tilde_02_t = 0;
                saw_tilde_02_lastSyncPhase = 0;
                saw_tilde_02_lastSyncDiff = 0;
                saw_tilde_02_didSync = false;
                saw_tilde_02_dcblocker_xm1 = 0;
                saw_tilde_02_dcblocker_ym1 = 0;
                saw_tilde_02_setupDone = false;
                numberobj_04_currentFormat = 6;
                numberobj_04_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number p_02_target;
                number selector_03_onoff;
                number cycle_tilde_02_frequency;
                number cycle_tilde_02_phase_offset;
                number dspexpr_04_in1;
                number dspexpr_04_in2;
                number expr_03_in1;
                number expr_03_in2;
                number expr_03_out1;
                number codebox_06_in1;
                number codebox_06_in2;
                number codebox_06_out1;
                number unpack_03_out1;
                number unpack_03_out2;
                number tri_tilde_02_frequency;
                number tri_tilde_02_pulsewidth;
                number tri_tilde_02_syncPhase;
                number rect_tilde_02_frequency;
                number rect_tilde_02_pulsewidth;
                number rect_tilde_02_syncPhase;
                number saw_tilde_02_frequency;
                number saw_tilde_02_syncPhase;
                number codebox_07_in1;
                number codebox_07_out1;
                number codebox_08_in1;
                number codebox_08_in2;
                number codebox_08_out1;
                number numberobj_04_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[5];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                Float64BufferRef cycle_tilde_02_buffer;
                long cycle_tilde_02_wrap;
                uint32_t cycle_tilde_02_phasei;
                SampleValue cycle_tilde_02_f2i;
                number cycle_tilde_02_ph_currentPhase;
                number cycle_tilde_02_ph_conv;
                bool cycle_tilde_02_setupDone;
                int midiparse_03_parser_status;
                int midiparse_03_parser_byte1;
                number tri_tilde_02_t;
                number tri_tilde_02_lastSyncPhase;
                number tri_tilde_02_lastSyncDiff;
                bool tri_tilde_02_didSync;
                number tri_tilde_02_yn;
                number tri_tilde_02_yn1;
                number tri_tilde_02_yn2;
                number tri_tilde_02_yn3;
                number tri_tilde_02_flg;
                number tri_tilde_02_app_correction;
                number tri_tilde_02_dcblocker_xm1;
                number tri_tilde_02_dcblocker_ym1;
                bool tri_tilde_02_setupDone;
                number rect_tilde_02_xHistory;
                number rect_tilde_02_yHistory;
                number rect_tilde_02_t;
                number rect_tilde_02_lastSyncPhase;
                number rect_tilde_02_lastSyncDiff;
                bool rect_tilde_02_didSync;
                number saw_tilde_02_t;
                number saw_tilde_02_lastSyncPhase;
                number saw_tilde_02_lastSyncDiff;
                bool saw_tilde_02_didSync;
                number saw_tilde_02_dcblocker_xm1;
                number saw_tilde_02_dcblocker_ym1;
                bool saw_tilde_02_setupDone;
                Int numberobj_04_currentFormat;
                number numberobj_04_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                RNBOSubpatcher_26* p_02;
            
    };
    
    class RNBOSubpatcher_31 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_32;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_31()
            {
            }
            
            ~RNBOSubpatcher_31()
            {
            }
            
            virtual RNBOSubpatcher_32* getPatcher() const {
                return static_cast<RNBOSubpatcher_32 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, -1468824490, false);
            }
            
            Index vectorsize() const {
                return this->vs;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
            
                this->adsr_02_perform(
                    this->adsr_02_attack,
                    this->adsr_02_decay,
                    this->adsr_02_sustain,
                    this->adsr_02_release,
                    this->zeroBuffer,
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->adsr_02_triggerBuf = resizeSignal(this->adsr_02_triggerBuf, this->maxvs, maxBlockSize);
                    this->adsr_02_triggerValueBuf = resizeSignal(this->adsr_02_triggerValueBuf, this->maxvs, maxBlockSize);
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->adsr_02_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case -1468824490:
                    {
                    this->adsr_02_mute_bang();
                    break;
                    }
                }
            }
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void eventinlet_25_out1_bang_bang() {}
            
            void eventinlet_25_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->midiparse_04_midiin_set(converted);
                }
            }
            
            void eventinlet_26_out1_bang_bang() {}
            
            void eventinlet_26_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_02_attack_set(converted);
                }
            }
            
            void eventinlet_27_out1_bang_bang() {}
            
            void eventinlet_27_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_02_decay_set(converted);
                }
            }
            
            void eventinlet_28_out1_bang_bang() {}
            
            void eventinlet_28_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_02_sustain_set(converted);
                }
            }
            
            void eventinlet_29_out1_bang_bang() {}
            
            void eventinlet_29_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_02_release_set(converted);
                }
            }
            
            void adsr_02_mute_bang() {}
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void adsr_02_attack_set(number v) {
                this->adsr_02_attack = v;
            }
            
            void eventinlet_26_out1_number_set(number v) {
                this->adsr_02_attack_set(v);
            }
            
            void adsr_02_decay_set(number v) {
                this->adsr_02_decay = v;
            }
            
            void eventinlet_27_out1_number_set(number v) {
                this->adsr_02_decay_set(v);
            }
            
            void adsr_02_sustain_set(number v) {
                this->adsr_02_sustain = v;
            }
            
            void eventinlet_28_out1_number_set(number v) {
                this->adsr_02_sustain_set(v);
            }
            
            void adsr_02_release_set(number v) {
                this->adsr_02_release = v;
            }
            
            void eventinlet_29_out1_number_set(number v) {
                this->adsr_02_release_set(v);
            }
            
            void midiparse_04_channel_set(number ) {}
            
            void adsr_02_trigger_number_set(number v) {
                this->adsr_02_trigger_number = v;
            
                if (v != 0)
                    this->adsr_02_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;
            
                for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
                    this->adsr_02_triggerValueBuf[(Index)i] = v;
                }
            }
            
            void expr_04_out1_set(number v) {
                this->expr_04_out1 = v;
                this->adsr_02_trigger_number_set(this->expr_04_out1);
            }
            
            void expr_04_in1_set(number in1) {
                this->expr_04_in1 = in1;
            
                this->expr_04_out1_set(
                    (this->expr_04_in2 == 0 ? 0 : (this->expr_04_in2 == 0. ? 0. : this->expr_04_in1 / this->expr_04_in2))
                );//#map:EnvelopeII//_obj-36:1
            }
            
            void unpack_04_out2_set(number v) {
                this->unpack_04_out2 = v;
                this->expr_04_in1_set(v);
            }
            
            void unpack_04_out1_set(number v) {
                this->unpack_04_out1 = v;
            }
            
            void unpack_04_input_list_set(const list& v) {
                if (v->length > 1)
                    this->unpack_04_out2_set(trunc(v[1]));
            
                if (v->length > 0)
                    this->unpack_04_out1_set(trunc(v[0]));
            }
            
            void midiparse_04_noteonoroff_set(const list& v) {
                this->unpack_04_input_list_set(v);
            }
            
            void midiparse_04_polypressure_set(const list& ) {}
            
            void midiparse_04_controlchange_set(const list& ) {}
            
            void midiparse_04_programchange_set(number ) {}
            
            void midiparse_04_aftertouch_set(number ) {}
            
            void midiparse_04_pitchbend_set(number ) {}
            
            void midiparse_04_midiin_set(number midivalue) {
                list result = this->midiparse_04_parser_next(midivalue);
            
                switch ((int)result[0]) {
                case 0:
                    {
                    this->midiparse_04_channel_set(result[3]);
                    this->midiparse_04_noteonoroff_set({result[1], result[2]});
                    break;
                    }
                case 1:
                    {
                    this->midiparse_04_channel_set(result[3]);
                    this->midiparse_04_polypressure_set({result[1], result[2]});
                    break;
                    }
                case 2:
                    {
                    this->midiparse_04_channel_set(result[3]);
                    this->midiparse_04_controlchange_set({result[1], result[2]});
                    break;
                    }
                case 3:
                    {
                    this->midiparse_04_channel_set(result[2]);
                    this->midiparse_04_programchange_set(result[1]);
                    break;
                    }
                case 4:
                    {
                    this->midiparse_04_channel_set(result[2]);
                    this->midiparse_04_aftertouch_set(result[1]);
                    break;
                    }
                case 5:
                    {
                    this->midiparse_04_channel_set(result[2]);
                    this->midiparse_04_pitchbend_set(result[1]);
                    break;
                    }
                }
            }
            
            void eventinlet_25_out1_number_set(number v) {
                this->midiparse_04_midiin_set(v);
            }
            
            void adsr_02_perform(
                number attack,
                number decay,
                number sustain,
                number release,
                const SampleValue * trigger_signal,
                SampleValue * out,
                Index n
            ) {
                RNBO_UNUSED(trigger_signal);
                auto __adsr_02_trigger_number = this->adsr_02_trigger_number;
                auto __adsr_02_time = this->adsr_02_time;
                auto __adsr_02_amplitude = this->adsr_02_amplitude;
                auto __adsr_02_outval = this->adsr_02_outval;
                auto __adsr_02_startingpoint = this->adsr_02_startingpoint;
                auto __adsr_02_phase = this->adsr_02_phase;
                auto __adsr_02_legato = this->adsr_02_legato;
                auto __adsr_02_lastTriggerVal = this->adsr_02_lastTriggerVal;
                auto __adsr_02_maxsustain = this->adsr_02_maxsustain;
                auto __adsr_02_mspersamp = this->adsr_02_mspersamp;
                bool bangMute = false;
            
                for (Index i = 0; i < n; i++) {
                    number clampedattack = (attack > __adsr_02_mspersamp ? attack : __adsr_02_mspersamp);
                    number clampeddecay = (decay > __adsr_02_mspersamp ? decay : __adsr_02_mspersamp);
                    number clampedsustain = (__adsr_02_maxsustain > __adsr_02_mspersamp ? __adsr_02_maxsustain : __adsr_02_mspersamp);
                    number clampedrelease = (release > __adsr_02_mspersamp ? release : __adsr_02_mspersamp);
                    number currentTriggerVal = this->adsr_02_triggerValueBuf[(Index)i];
            
                    if ((__adsr_02_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_02_triggerBuf[(Index)i] == 1) {
                        if ((bool)(__adsr_02_legato)) {
                            if (__adsr_02_phase != 0) {
                                __adsr_02_startingpoint = __adsr_02_outval;
                            } else {
                                __adsr_02_startingpoint = 0;
                            }
                        } else {
                            __adsr_02_startingpoint = 0;
                        }
            
                        __adsr_02_amplitude = currentTriggerVal;
                        __adsr_02_phase = 1;
                        __adsr_02_time = 0.0;
                        bangMute = false;
                    } else if (__adsr_02_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
                        if (__adsr_02_phase != 4 && __adsr_02_phase != 0) {
                            __adsr_02_phase = 4;
                            __adsr_02_amplitude = __adsr_02_outval;
                            __adsr_02_time = 0.0;
                        }
                    }
            
                    __adsr_02_time += __adsr_02_mspersamp;
            
                    if (__adsr_02_phase == 0) {
                        __adsr_02_outval = 0;
                    } else if (__adsr_02_phase == 1) {
                        if (__adsr_02_time > clampedattack) {
                            __adsr_02_time -= clampedattack;
                            __adsr_02_phase = 2;
                            __adsr_02_outval = __adsr_02_amplitude;
                        } else {
                            __adsr_02_outval = (__adsr_02_amplitude - __adsr_02_startingpoint) * __adsr_02_time / clampedattack + __adsr_02_startingpoint;
                        }
                    } else if (__adsr_02_phase == 2) {
                        if (__adsr_02_time > clampeddecay) {
                            __adsr_02_time -= clampeddecay;
                            __adsr_02_phase = 3;
                            __adsr_02_outval = __adsr_02_amplitude * sustain;
                        } else {
                            __adsr_02_outval = __adsr_02_amplitude * sustain + (__adsr_02_amplitude - __adsr_02_amplitude * sustain) * (1. - __adsr_02_time / clampeddecay);
                        }
                    } else if (__adsr_02_phase == 3) {
                        if (__adsr_02_time > clampedsustain && __adsr_02_maxsustain > -1) {
                            __adsr_02_time -= clampedsustain;
                            __adsr_02_phase = 4;
                            __adsr_02_amplitude = __adsr_02_outval;
                        } else {
                            __adsr_02_outval = __adsr_02_amplitude * sustain;
                        }
                    } else if (__adsr_02_phase == 4) {
                        if (__adsr_02_time > clampedrelease) {
                            __adsr_02_time = 0;
                            __adsr_02_phase = 0;
                            __adsr_02_outval = 0;
                            __adsr_02_amplitude = 0;
                            bangMute = true;
                        } else {
                            __adsr_02_outval = __adsr_02_amplitude * (1.0 - __adsr_02_time / clampedrelease);
                        }
                    }
            
                    out[(Index)i] = __adsr_02_outval;
                    this->adsr_02_triggerBuf[(Index)i] = 0;
                    this->adsr_02_triggerValueBuf[(Index)i] = __adsr_02_trigger_number;
                    __adsr_02_lastTriggerVal = currentTriggerVal;
                }
            
                if ((bool)(bangMute)) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -1468824490,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;
                }
            
                this->adsr_02_lastTriggerVal = __adsr_02_lastTriggerVal;
                this->adsr_02_phase = __adsr_02_phase;
                this->adsr_02_startingpoint = __adsr_02_startingpoint;
                this->adsr_02_outval = __adsr_02_outval;
                this->adsr_02_amplitude = __adsr_02_amplitude;
                this->adsr_02_time = __adsr_02_time;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            list midiparse_04_parser_next(number midiin) {
                int midivalue = (int)(trunc(midiin));
                list result = list(-1);
                number resetByte1 = false;
            
                if (midivalue > 127) {
                    this->midiparse_04_parser_status = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0xFF);
                    this->midiparse_04_parser_byte1 = -1;
                } else {
                    switch ((int)((BinOpInt)this->midiparse_04_parser_status & (BinOpInt)0xF0)) {
                    case 0xB0:
                        {
                        if (this->midiparse_04_parser_byte1 == -1) {
                            this->midiparse_04_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                2,
                                this->midiparse_04_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_04_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xA0:
                        {
                        if (this->midiparse_04_parser_byte1 == -1) {
                            this->midiparse_04_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                1,
                                this->midiparse_04_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_04_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xE0:
                        {
                        if (this->midiparse_04_parser_byte1 == -1) {
                            this->midiparse_04_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            number pitchbend;
            
                            {
                                number val = this->midiparse_04_parser_byte1 + ((BinOpInt)(((BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32)));
            
                                {
                                    val -= 0x2000;
                                    pitchbend = val / (number)8192;
                                }
                            }
            
                            result = {
                                5,
                                pitchbend,
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_04_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xD0:
                        {
                        result = {
                            4,
                            (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                            (BinOpInt)((BinOpInt)(1 + this->midiparse_04_parser_status) & (BinOpInt)0x0F)
                        };
            
                        break;
                        }
                    case 0x90:
                        {
                        if (this->midiparse_04_parser_byte1 == -1) {
                            this->midiparse_04_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                0,
                                this->midiparse_04_parser_byte1,
                                (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_04_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    case 0xC0:
                        {
                        result = {
                            3,
                            (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                            (BinOpInt)((BinOpInt)(1 + this->midiparse_04_parser_status) & (BinOpInt)0x0F)
                        };
            
                        break;
                        }
                    case 0x80:
                        {
                        if (this->midiparse_04_parser_byte1 == -1) {
                            this->midiparse_04_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                        } else {
                            result = {
                                0,
                                this->midiparse_04_parser_byte1,
                                0,
                                (BinOpInt)((BinOpInt)(1 + this->midiparse_04_parser_status) & (BinOpInt)0x0F)
                            };
            
                            resetByte1 = true;
                        }
            
                        break;
                        }
                    default:
                        {
                        result = {-1};
                        }
                    }
                }
            
                if (result->length > 1) {
                    result->push(this->midiparse_04_parser_status);
                    result->push(this->midiparse_04_parser_byte1);
                    result->push(midivalue);
                }
            
                if ((bool)(resetByte1)) {
                    this->midiparse_04_parser_byte1 = -1;
                }
            
                return result;
            }
            
            void midiparse_04_parser_reset() {
                this->midiparse_04_parser_status = -1;
                this->midiparse_04_parser_byte1 = -1;
            }
            
            void adsr_02_dspsetup(bool force) {
                if ((bool)(this->adsr_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->adsr_02_mspersamp = (number)1000 / this->sr;
                this->adsr_02_setupDone = true;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                expr_04_in1 = 0;
                expr_04_in2 = 127;
                expr_04_out1 = 0;
                unpack_04_out1 = 0;
                unpack_04_out2 = 0;
                adsr_02_trigger_number = 0;
                adsr_02_attack = 0;
                adsr_02_decay = 0;
                adsr_02_sustain = 0;
                adsr_02_release = 0;
                adsr_02_legato = 0;
                adsr_02_maxsustain = -1;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                midiparse_04_parser_status = -1;
                midiparse_04_parser_byte1 = -1;
                adsr_02_phase = 3;
                adsr_02_mspersamp = 0;
                adsr_02_time = 0;
                adsr_02_lastTriggerVal = 0;
                adsr_02_amplitude = 0;
                adsr_02_outval = 0;
                adsr_02_startingpoint = 0;
                adsr_02_triggerBuf = nullptr;
                adsr_02_triggerValueBuf = nullptr;
                adsr_02_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number expr_04_in1;
                number expr_04_in2;
                number expr_04_out1;
                number unpack_04_out1;
                number unpack_04_out2;
                number adsr_02_trigger_number;
                number adsr_02_attack;
                number adsr_02_decay;
                number adsr_02_sustain;
                number adsr_02_release;
                number adsr_02_legato;
                number adsr_02_maxsustain;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                int midiparse_04_parser_status;
                int midiparse_04_parser_byte1;
                Int adsr_02_phase;
                number adsr_02_mspersamp;
                number adsr_02_time;
                number adsr_02_lastTriggerVal;
                number adsr_02_amplitude;
                number adsr_02_outval;
                number adsr_02_startingpoint;
                signal adsr_02_triggerBuf;
                signal adsr_02_triggerValueBuf;
                bool adsr_02_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_32()
    {
    }
    
    ~RNBOSubpatcher_32()
    {
        delete this->p_03;
        delete this->p_04;
        delete this->p_05;
        delete this->p_06;
        delete this->p_07;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    Index getNumMidiInputPorts() const {
        return 1;
    }
    
    void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
        this->updateTime(time);
        this->midiin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->bendin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->midiin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->bendin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    }
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    
        if (this->getIsMuted())
            return;
    
        this->p_04_perform(this->signals[0], n);
        this->p_05_perform(this->signals[1], n);
        this->dspexpr_05_perform(this->signals[0], this->signals[1], this->signals[2], n);
        this->onepole_tilde_01_perform(this->signals[2], this->onepole_tilde_01_freqInHz, this->signals[1], n);
        this->p_06_perform(this->signals[2], n);
        this->p_07_perform(this->signals[0], n);
        this->dspexpr_06_perform(this->signals[2], this->signals[0], this->signals[3], n);
        this->onepole_tilde_02_perform(this->signals[3], this->onepole_tilde_02_freqInHz, this->signals[0], n);
        this->p_03_perform(this->signals[1], this->signals[0], this->signals[3], this->signals[2], n);
        this->signaladder_01_perform(this->signals[3], out1, out1, n);
        this->signaladder_02_perform(this->signals[2], out2, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 4; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->onepole_tilde_01_dspsetup(forceDSPSetup);
        this->onepole_tilde_02_dspsetup(forceDSPSetup);
        this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_05->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_06->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_07->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    void setVoiceIndex(Index index)  {
        this->_voiceIndex = index;
        this->p_03->setVoiceIndex(index);
        this->p_04->setVoiceIndex(index);
        this->p_05->setVoiceIndex(index);
        this->p_06->setVoiceIndex(index);
        this->p_07->setVoiceIndex(index);
    }
    
    void setNoteNumber(Int noteNumber)  {
        this->_noteNumber = noteNumber;
        this->p_03->setNoteNumber(noteNumber);
        this->p_04->setNoteNumber(noteNumber);
        this->p_05->setNoteNumber(noteNumber);
        this->p_06->setNoteNumber(noteNumber);
        this->p_07->setNoteNumber(noteNumber);
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_03 = new RNBOSubpatcher_27();
        this->p_03->setEngineAndPatcher(this->getEngine(), this);
        this->p_03->initialize();
        this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
        this->p_04 = new RNBOSubpatcher_28();
        this->p_04->setEngineAndPatcher(this->getEngine(), this);
        this->p_04->initialize();
        this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
        this->p_05 = new RNBOSubpatcher_29();
        this->p_05->setEngineAndPatcher(this->getEngine(), this);
        this->p_05->initialize();
        this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));
        this->p_06 = new RNBOSubpatcher_30();
        this->p_06->setEngineAndPatcher(this->getEngine(), this);
        this->p_06->initialize();
        this->p_06->setParameterOffset(this->getParameterOffset(this->p_06));
        this->p_07 = new RNBOSubpatcher_31();
        this->p_07->setEngineAndPatcher(this->getEngine(), this);
        this->p_07->initialize();
        this->p_07->setParameterOffset(this->getParameterOffset(this->p_07));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "Output"));
        this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "OscillatorI"));
        this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "EnvelopeI"));
        this->p_06->getPreset(getSubState(getSubState(preset, "__sps"), "OscillatorII"));
        this->p_07->getPreset(getSubState(getSubState(preset, "__sps"), "EnvelopeII"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_01_value_set(v);
            break;
            }
        case 1:
            {
            this->param_02_value_set(v);
            break;
            }
        case 2:
            {
            this->param_03_value_set(v);
            break;
            }
        case 3:
            {
            this->param_04_value_set(v);
            break;
            }
        case 4:
            {
            this->param_05_value_set(v);
            break;
            }
        case 5:
            {
            this->param_06_value_set(v);
            break;
            }
        case 6:
            {
            this->param_07_value_set(v);
            break;
            }
        case 7:
            {
            this->param_08_value_set(v);
            break;
            }
        case 8:
            {
            this->param_09_value_set(v);
            break;
            }
        case 9:
            {
            this->param_10_value_set(v);
            break;
            }
        case 10:
            {
            this->param_11_value_set(v);
            break;
            }
        case 11:
            {
            this->param_12_value_set(v);
            break;
            }
        case 12:
            {
            this->param_13_value_set(v);
            break;
            }
        case 13:
            {
            this->param_14_value_set(v);
            break;
            }
        case 14:
            {
            this->param_15_value_set(v);
            break;
            }
        case 15:
            {
            this->param_16_value_set(v);
            break;
            }
        case 16:
            {
            this->param_17_value_set(v);
            break;
            }
        case 17:
            {
            this->param_18_value_set(v);
            break;
            }
        case 18:
            {
            this->param_19_value_set(v);
            break;
            }
        default:
            {
            index -= 19;
    
            if (index < this->p_03->getNumParameters())
                this->p_03->setParameterValue(index, v, time);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                this->p_04->setParameterValue(index, v, time);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                this->p_05->setParameterValue(index, v, time);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                this->p_06->setParameterValue(index, v, time);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                this->p_07->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_01_value;
            }
        case 1:
            {
            return this->param_02_value;
            }
        case 2:
            {
            return this->param_03_value;
            }
        case 3:
            {
            return this->param_04_value;
            }
        case 4:
            {
            return this->param_05_value;
            }
        case 5:
            {
            return this->param_06_value;
            }
        case 6:
            {
            return this->param_07_value;
            }
        case 7:
            {
            return this->param_08_value;
            }
        case 8:
            {
            return this->param_09_value;
            }
        case 9:
            {
            return this->param_10_value;
            }
        case 10:
            {
            return this->param_11_value;
            }
        case 11:
            {
            return this->param_12_value;
            }
        case 12:
            {
            return this->param_13_value;
            }
        case 13:
            {
            return this->param_14_value;
            }
        case 14:
            {
            return this->param_15_value;
            }
        case 15:
            {
            return this->param_16_value;
            }
        case 16:
            {
            return this->param_17_value;
            }
        case 17:
            {
            return this->param_18_value;
            }
        case 18:
            {
            return this->param_19_value;
            }
        default:
            {
            index -= 19;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterValue(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterValue(index);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->getParameterValue(index);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->getParameterValue(index);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterValue getPolyParameterValue(PatcherInterface** voices, ParameterIndex index)  {
        switch (index) {
        default:
            {
            return voices[0]->getParameterValue(index);
            }
        }
    }
    
    void setPolyParameterValue(
        PatcherInterface** voices,
        ParameterIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        switch (index) {
        default:
            {
            for (Index i = 0; i < 8; i++)
                voices[i]->setParameterValue(index, value, time);
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 19 + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "ModulationMode";
            }
        case 1:
            {
            return "WaveformI";
            }
        case 2:
            {
            return "CoarseI";
            }
        case 3:
            {
            return "BendRangeI";
            }
        case 4:
            {
            return "FilterICutOff";
            }
        case 5:
            {
            return "EnvIAttack";
            }
        case 6:
            {
            return "EnvIDecay";
            }
        case 7:
            {
            return "EnvISustain";
            }
        case 8:
            {
            return "EnvIRelease";
            }
        case 9:
            {
            return "VolumeI";
            }
        case 10:
            {
            return "WaveformII";
            }
        case 11:
            {
            return "CoarseII";
            }
        case 12:
            {
            return "BendRangeII";
            }
        case 13:
            {
            return "FilterIICutOff";
            }
        case 14:
            {
            return "EnvIIAttack";
            }
        case 15:
            {
            return "EnvIIDecay";
            }
        case 16:
            {
            return "EnvIISustain";
            }
        case 17:
            {
            return "EnvIIRelease";
            }
        case 18:
            {
            return "VolumeII";
            }
        default:
            {
            index -= 19;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterName(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterName(index);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->getParameterName(index);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->getParameterName(index);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "poly/ModulationMode";
            }
        case 1:
            {
            return "poly/WaveformI";
            }
        case 2:
            {
            return "poly/CoarseI";
            }
        case 3:
            {
            return "poly/BendRangeI";
            }
        case 4:
            {
            return "poly/FilterICutOff";
            }
        case 5:
            {
            return "poly/EnvIAttack";
            }
        case 6:
            {
            return "poly/EnvIDecay";
            }
        case 7:
            {
            return "poly/EnvISustain";
            }
        case 8:
            {
            return "poly/EnvIRelease";
            }
        case 9:
            {
            return "poly/VolumeI";
            }
        case 10:
            {
            return "poly/WaveformII";
            }
        case 11:
            {
            return "poly/CoarseII";
            }
        case 12:
            {
            return "poly/BendRangeII";
            }
        case 13:
            {
            return "poly/FilterIICutOff";
            }
        case 14:
            {
            return "poly/EnvIIAttack";
            }
        case 15:
            {
            return "poly/EnvIIDecay";
            }
        case 16:
            {
            return "poly/EnvIISustain";
            }
        case 17:
            {
            return "poly/EnvIIRelease";
            }
        case 18:
            {
            return "poly/VolumeII";
            }
        default:
            {
            index -= 19;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterId(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterId(index);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->getParameterId(index);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->getParameterId(index);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 1;
                info->max = 2;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 4;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 2:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = -44;
                info->max = 44;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 3:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 2;
                info->min = -22;
                info->max = 22;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 4:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 20000;
                info->min = 10;
                info->max = 20000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 5:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 5;
                info->min = 1;
                info->max = 20000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 6:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 50;
                info->min = 1;
                info->max = 20000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 7:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.5;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 8:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 50;
                info->min = 1;
                info->max = 20000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 9:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.3;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 10:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 4;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 11:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = -44;
                info->max = 44;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 12:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 2;
                info->min = -22;
                info->max = 22;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 13:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 20000;
                info->min = 10;
                info->max = 20000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 14:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 5;
                info->min = 1;
                info->max = 20000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 15:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 50;
                info->min = 1;
                info->max = 20000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 16:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.5;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 17:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 50;
                info->min = 1;
                info->max = 20000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 18:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.3;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            default:
                {
                index -= 19;
    
                if (index < this->p_03->getNumParameters())
                    this->p_03->getParameterInfo(index, info);
    
                index -= this->p_03->getNumParameters();
    
                if (index < this->p_04->getNumParameters())
                    this->p_04->getParameterInfo(index, info);
    
                index -= this->p_04->getNumParameters();
    
                if (index < this->p_05->getNumParameters())
                    this->p_05->getParameterInfo(index, info);
    
                index -= this->p_05->getNumParameters();
    
                if (index < this->p_06->getNumParameters())
                    this->p_06->getParameterInfo(index, info);
    
                index -= this->p_06->getNumParameters();
    
                if (index < this->p_07->getNumParameters())
                    this->p_07->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        if (this->_voiceIndex == 1)
            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_03)
            return 19;
    
        if (subpatcher == this->p_04)
            return 19 + this->p_03->getNumParameters();
    
        if (subpatcher == this->p_05)
            return 19 + this->p_03->getNumParameters() + this->p_04->getNumParameters();
    
        if (subpatcher == this->p_06)
            return 19 + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters();
    
        if (subpatcher == this->p_07)
            return 19 + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 7:
        case 9:
        case 16:
        case 18:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 1:
        case 10:
            {
            {
                value = (value < 0 ? 0 : (value > 4 ? 4 : value));
                ParameterValue normalizedValue = (value - 0) / (4 - 0);
                return normalizedValue;
            }
            }
        case 0:
            {
            {
                value = (value < 1 ? 1 : (value > 2 ? 2 : value));
                ParameterValue normalizedValue = (value - 1) / (2 - 1);
                return normalizedValue;
            }
            }
        case 5:
        case 6:
        case 8:
        case 14:
        case 15:
        case 17:
            {
            {
                value = (value < 1 ? 1 : (value > 20000 ? 20000 : value));
                ParameterValue normalizedValue = (value - 1) / (20000 - 1);
                return normalizedValue;
            }
            }
        case 4:
        case 13:
            {
            {
                value = (value < 10 ? 10 : (value > 20000 ? 20000 : value));
                ParameterValue normalizedValue = (value - 10) / (20000 - 10);
                return normalizedValue;
            }
            }
        case 2:
        case 11:
            {
            {
                value = (value < -44 ? -44 : (value > 44 ? 44 : value));
                ParameterValue normalizedValue = (value - -44) / (44 - -44);
                return normalizedValue;
            }
            }
        case 3:
        case 12:
            {
            {
                value = (value < -22 ? -22 : (value > 22 ? 22 : value));
                ParameterValue normalizedValue = (value - -22) / (22 - -22);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 19;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 7:
        case 9:
        case 16:
        case 18:
            {
            {
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 1:
        case 10:
            {
            {
                {
                    return 0 + value * (4 - 0);
                }
            }
            }
        case 0:
            {
            {
                {
                    return 1 + value * (2 - 1);
                }
            }
            }
        case 5:
        case 6:
        case 8:
        case 14:
        case 15:
        case 17:
            {
            {
                {
                    return 1 + value * (20000 - 1);
                }
            }
            }
        case 4:
        case 13:
            {
            {
                {
                    return 10 + value * (20000 - 10);
                }
            }
            }
        case 2:
        case 11:
            {
            {
                {
                    return -44 + value * (44 - -44);
                }
            }
            }
        case 3:
        case 12:
            {
            {
                {
                    return -22 + value * (22 - -22);
                }
            }
            }
        default:
            {
            index -= 19;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_01_value_constrain(value);
            }
        case 1:
            {
            return this->param_02_value_constrain(value);
            }
        case 2:
            {
            return this->param_03_value_constrain(value);
            }
        case 3:
            {
            return this->param_04_value_constrain(value);
            }
        case 4:
            {
            return this->param_05_value_constrain(value);
            }
        case 5:
            {
            return this->param_06_value_constrain(value);
            }
        case 6:
            {
            return this->param_07_value_constrain(value);
            }
        case 7:
            {
            return this->param_08_value_constrain(value);
            }
        case 8:
            {
            return this->param_09_value_constrain(value);
            }
        case 9:
            {
            return this->param_10_value_constrain(value);
            }
        case 10:
            {
            return this->param_11_value_constrain(value);
            }
        case 11:
            {
            return this->param_12_value_constrain(value);
            }
        case 12:
            {
            return this->param_13_value_constrain(value);
            }
        case 13:
            {
            return this->param_14_value_constrain(value);
            }
        case 14:
            {
            return this->param_15_value_constrain(value);
            }
        case 15:
            {
            return this->param_16_value_constrain(value);
            }
        case 16:
            {
            return this->param_17_value_constrain(value);
            }
        case 17:
            {
            return this->param_18_value_constrain(value);
            }
        case 18:
            {
            return this->param_19_value_constrain(value);
            }
        default:
            {
            index -= 19;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->constrainParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->constrainParameterValue(index, value);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->constrainParameterValue(index, value);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->constrainParameterValue(index, value);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_03->processNumMessage(tag, objectId, time, payload);
        this->p_04->processNumMessage(tag, objectId, time, payload);
        this->p_05->processNumMessage(tag, objectId, time, payload);
        this->p_06->processNumMessage(tag, objectId, time, payload);
        this->p_07->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_03->processListMessage(tag, objectId, time, payload);
        this->p_04->processListMessage(tag, objectId, time, payload);
        this->p_05->processListMessage(tag, objectId, time, payload);
        this->p_06->processListMessage(tag, objectId, time, payload);
        this->p_07->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_03->processBangMessage(tag, objectId, time);
        this->p_04->processBangMessage(tag, objectId, time);
        this->p_05->processBangMessage(tag, objectId, time);
        this->p_06->processBangMessage(tag, objectId, time);
        this->p_07->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        auto subpatchResult_0 = this->p_03->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_04->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_05->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
        auto subpatchResult_3 = this->p_06->resolveTag(tag);
    
        if (subpatchResult_3)
            return subpatchResult_3;
    
        auto subpatchResult_4 = this->p_07->resolveTag(tag);
    
        if (subpatchResult_4)
            return subpatchResult_4;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->p_03->processDataViewUpdate(index, time);
        this->p_04->processDataViewUpdate(index, time);
        this->p_05->processDataViewUpdate(index, time);
        this->p_06->processDataViewUpdate(index, time);
        this->p_07->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void param_01_value_set(number v) {
        v = this->param_01_value_constrain(v);
        this->param_01_value = v;
        this->sendParameter(0, false);
    
        if (this->param_01_value != this->param_01_lastValue) {
            this->getEngine()->presetTouched();
            this->param_01_lastValue = this->param_01_value;
        }
    
        this->p_03_in3_number_set(v);
    }
    
    void param_02_value_set(number v) {
        v = this->param_02_value_constrain(v);
        this->param_02_value = v;
        this->sendParameter(1, false);
    
        if (this->param_02_value != this->param_02_lastValue) {
            this->getEngine()->presetTouched();
            this->param_02_lastValue = this->param_02_value;
        }
    
        this->p_04_in2_number_set(v);
    }
    
    void param_03_value_set(number v) {
        v = this->param_03_value_constrain(v);
        this->param_03_value = v;
        this->sendParameter(2, false);
    
        if (this->param_03_value != this->param_03_lastValue) {
            this->getEngine()->presetTouched();
            this->param_03_lastValue = this->param_03_value;
        }
    
        this->p_04_in3_number_set(v);
    }
    
    void param_04_value_set(number v) {
        v = this->param_04_value_constrain(v);
        this->param_04_value = v;
        this->sendParameter(3, false);
    
        if (this->param_04_value != this->param_04_lastValue) {
            this->getEngine()->presetTouched();
            this->param_04_lastValue = this->param_04_value;
        }
    
        this->p_04_in4_number_set(v);
    }
    
    void param_05_value_set(number v) {
        v = this->param_05_value_constrain(v);
        this->param_05_value = v;
        this->sendParameter(4, false);
    
        if (this->param_05_value != this->param_05_lastValue) {
            this->getEngine()->presetTouched();
            this->param_05_lastValue = this->param_05_value;
        }
    
        this->onepole_tilde_01_freqInHz_set(v);
    }
    
    void param_06_value_set(number v) {
        v = this->param_06_value_constrain(v);
        this->param_06_value = v;
        this->sendParameter(5, false);
    
        if (this->param_06_value != this->param_06_lastValue) {
            this->getEngine()->presetTouched();
            this->param_06_lastValue = this->param_06_value;
        }
    
        this->p_05_in2_number_set(v);
    }
    
    void param_07_value_set(number v) {
        v = this->param_07_value_constrain(v);
        this->param_07_value = v;
        this->sendParameter(6, false);
    
        if (this->param_07_value != this->param_07_lastValue) {
            this->getEngine()->presetTouched();
            this->param_07_lastValue = this->param_07_value;
        }
    
        this->p_05_in3_number_set(v);
    }
    
    void param_08_value_set(number v) {
        v = this->param_08_value_constrain(v);
        this->param_08_value = v;
        this->sendParameter(7, false);
    
        if (this->param_08_value != this->param_08_lastValue) {
            this->getEngine()->presetTouched();
            this->param_08_lastValue = this->param_08_value;
        }
    
        this->p_05_in4_number_set(v);
    }
    
    void param_09_value_set(number v) {
        v = this->param_09_value_constrain(v);
        this->param_09_value = v;
        this->sendParameter(8, false);
    
        if (this->param_09_value != this->param_09_lastValue) {
            this->getEngine()->presetTouched();
            this->param_09_lastValue = this->param_09_value;
        }
    
        this->p_05_in5_number_set(v);
    }
    
    void param_10_value_set(number v) {
        v = this->param_10_value_constrain(v);
        this->param_10_value = v;
        this->sendParameter(9, false);
    
        if (this->param_10_value != this->param_10_lastValue) {
            this->getEngine()->presetTouched();
            this->param_10_lastValue = this->param_10_value;
        }
    
        this->p_04_in5_number_set(v);
    }
    
    void param_11_value_set(number v) {
        v = this->param_11_value_constrain(v);
        this->param_11_value = v;
        this->sendParameter(10, false);
    
        if (this->param_11_value != this->param_11_lastValue) {
            this->getEngine()->presetTouched();
            this->param_11_lastValue = this->param_11_value;
        }
    
        this->p_06_in2_number_set(v);
    }
    
    void param_12_value_set(number v) {
        v = this->param_12_value_constrain(v);
        this->param_12_value = v;
        this->sendParameter(11, false);
    
        if (this->param_12_value != this->param_12_lastValue) {
            this->getEngine()->presetTouched();
            this->param_12_lastValue = this->param_12_value;
        }
    
        this->p_06_in3_number_set(v);
    }
    
    void param_13_value_set(number v) {
        v = this->param_13_value_constrain(v);
        this->param_13_value = v;
        this->sendParameter(12, false);
    
        if (this->param_13_value != this->param_13_lastValue) {
            this->getEngine()->presetTouched();
            this->param_13_lastValue = this->param_13_value;
        }
    
        this->p_06_in4_number_set(v);
    }
    
    void param_14_value_set(number v) {
        v = this->param_14_value_constrain(v);
        this->param_14_value = v;
        this->sendParameter(13, false);
    
        if (this->param_14_value != this->param_14_lastValue) {
            this->getEngine()->presetTouched();
            this->param_14_lastValue = this->param_14_value;
        }
    
        this->onepole_tilde_02_freqInHz_set(v);
    }
    
    void param_15_value_set(number v) {
        v = this->param_15_value_constrain(v);
        this->param_15_value = v;
        this->sendParameter(14, false);
    
        if (this->param_15_value != this->param_15_lastValue) {
            this->getEngine()->presetTouched();
            this->param_15_lastValue = this->param_15_value;
        }
    
        this->p_07_in2_number_set(v);
    }
    
    void param_16_value_set(number v) {
        v = this->param_16_value_constrain(v);
        this->param_16_value = v;
        this->sendParameter(15, false);
    
        if (this->param_16_value != this->param_16_lastValue) {
            this->getEngine()->presetTouched();
            this->param_16_lastValue = this->param_16_value;
        }
    
        this->p_07_in3_number_set(v);
    }
    
    void param_17_value_set(number v) {
        v = this->param_17_value_constrain(v);
        this->param_17_value = v;
        this->sendParameter(16, false);
    
        if (this->param_17_value != this->param_17_lastValue) {
            this->getEngine()->presetTouched();
            this->param_17_lastValue = this->param_17_value;
        }
    
        this->p_07_in4_number_set(v);
    }
    
    void param_18_value_set(number v) {
        v = this->param_18_value_constrain(v);
        this->param_18_value = v;
        this->sendParameter(17, false);
    
        if (this->param_18_value != this->param_18_lastValue) {
            this->getEngine()->presetTouched();
            this->param_18_lastValue = this->param_18_value;
        }
    
        this->p_07_in5_number_set(v);
    }
    
    void param_19_value_set(number v) {
        v = this->param_19_value_constrain(v);
        this->param_19_value = v;
        this->sendParameter(18, false);
    
        if (this->param_19_value != this->param_19_lastValue) {
            this->getEngine()->presetTouched();
            this->param_19_lastValue = this->param_19_value;
        }
    
        this->p_06_in5_number_set(v);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->p_03->initializeObjects();
        this->p_04->initializeObjects();
        this->p_05->initializeObjects();
        this->p_06->initializeObjects();
        this->p_07->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_03->startup();
        this->p_04->startup();
        this->p_05->startup();
        this->p_06->startup();
        this->p_07->startup();
    }
    
    void allocateDataRefs() {
        this->p_03->allocateDataRefs();
        this->p_04->allocateDataRefs();
        this->p_05->allocateDataRefs();
        this->p_06->allocateDataRefs();
        this->p_07->allocateDataRefs();
    }
    
    number param_01_value_constrain(number v) const {
        v = (v > 2 ? 2 : (v < 1 ? 1 : v));
        return v;
    }
    
    void p_03_in3_number_set(number v) {
        this->p_03->updateTime(this->_currentTime);
        this->p_03->eventinlet_01_out1_number_set(v);
    }
    
    number param_02_value_constrain(number v) const {
        v = (v > 4 ? 4 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_04_in2_number_set(number v) {
        this->p_04->updateTime(this->_currentTime);
        this->p_04->eventinlet_07_out1_number_set(v);
    }
    
    number param_03_value_constrain(number v) const {
        v = (v > 44 ? 44 : (v < -44 ? -44 : v));
        return v;
    }
    
    void p_04_in3_number_set(number v) {
        this->p_04->updateTime(this->_currentTime);
        this->p_04->eventinlet_08_out1_number_set(v);
    }
    
    number param_04_value_constrain(number v) const {
        v = (v > 22 ? 22 : (v < -22 ? -22 : v));
        return v;
    }
    
    void p_04_in4_number_set(number v) {
        this->p_04->updateTime(this->_currentTime);
        this->p_04->eventinlet_10_out1_number_set(v);
    }
    
    number param_05_value_constrain(number v) const {
        v = (v > 20000 ? 20000 : (v < 10 ? 10 : v));
        return v;
    }
    
    void onepole_tilde_01_freqInHz_set(number v) {
        this->onepole_tilde_01_freqInHz = v;
    }
    
    number param_06_value_constrain(number v) const {
        v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
        return v;
    }
    
    void p_05_in2_number_set(number v) {
        this->p_05->updateTime(this->_currentTime);
        this->p_05->eventinlet_12_out1_number_set(v);
    }
    
    number param_07_value_constrain(number v) const {
        v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
        return v;
    }
    
    void p_05_in3_number_set(number v) {
        this->p_05->updateTime(this->_currentTime);
        this->p_05->eventinlet_13_out1_number_set(v);
    }
    
    number param_08_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_05_in4_number_set(number v) {
        this->p_05->updateTime(this->_currentTime);
        this->p_05->eventinlet_14_out1_number_set(v);
    }
    
    number param_09_value_constrain(number v) const {
        v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
        return v;
    }
    
    void p_05_in5_number_set(number v) {
        this->p_05->updateTime(this->_currentTime);
        this->p_05->eventinlet_15_out1_number_set(v);
    }
    
    number param_10_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_04_in5_number_set(number v) {
        this->p_04->updateTime(this->_currentTime);
        this->p_04->eventinlet_09_out1_number_set(v);
    }
    
    number param_11_value_constrain(number v) const {
        v = (v > 4 ? 4 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_06_in2_number_set(number v) {
        this->p_06->updateTime(this->_currentTime);
        this->p_06->eventinlet_21_out1_number_set(v);
    }
    
    number param_12_value_constrain(number v) const {
        v = (v > 44 ? 44 : (v < -44 ? -44 : v));
        return v;
    }
    
    void p_06_in3_number_set(number v) {
        this->p_06->updateTime(this->_currentTime);
        this->p_06->eventinlet_22_out1_number_set(v);
    }
    
    number param_13_value_constrain(number v) const {
        v = (v > 22 ? 22 : (v < -22 ? -22 : v));
        return v;
    }
    
    void p_06_in4_number_set(number v) {
        this->p_06->updateTime(this->_currentTime);
        this->p_06->eventinlet_24_out1_number_set(v);
    }
    
    number param_14_value_constrain(number v) const {
        v = (v > 20000 ? 20000 : (v < 10 ? 10 : v));
        return v;
    }
    
    void onepole_tilde_02_freqInHz_set(number v) {
        this->onepole_tilde_02_freqInHz = v;
    }
    
    number param_15_value_constrain(number v) const {
        v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
        return v;
    }
    
    void p_07_in2_number_set(number v) {
        this->p_07->updateTime(this->_currentTime);
        this->p_07->eventinlet_26_out1_number_set(v);
    }
    
    number param_16_value_constrain(number v) const {
        v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
        return v;
    }
    
    void p_07_in3_number_set(number v) {
        this->p_07->updateTime(this->_currentTime);
        this->p_07->eventinlet_27_out1_number_set(v);
    }
    
    number param_17_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_07_in4_number_set(number v) {
        this->p_07->updateTime(this->_currentTime);
        this->p_07->eventinlet_28_out1_number_set(v);
    }
    
    number param_18_value_constrain(number v) const {
        v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
        return v;
    }
    
    void p_07_in5_number_set(number v) {
        this->p_07->updateTime(this->_currentTime);
        this->p_07->eventinlet_29_out1_number_set(v);
    }
    
    number param_19_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_06_in5_number_set(number v) {
        this->p_06->updateTime(this->_currentTime);
        this->p_06->eventinlet_23_out1_number_set(v);
    }
    
    void p_05_in1_number_set(number v) {
        this->p_05->updateTime(this->_currentTime);
        this->p_05->eventinlet_11_out1_number_set(v);
    }
    
    void p_04_in1_number_set(number v) {
        this->p_04->updateTime(this->_currentTime);
        this->p_04->eventinlet_06_out1_number_set(v);
    }
    
    void midiin_01_midiout_set(number v) {
        this->p_05_in1_number_set(v);
        this->p_04_in1_number_set(v);
    }
    
    void midiin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(port);
        RNBO_UNUSED(channel);
        RNBO_UNUSED(status);
        Index i;
    
        for (i = 0; i < length; i++) {
            this->midiin_01_midiout_set(data[i]);
        }
    }
    
    void bendin_01_channel_set(number v) {
        this->bendin_01_channel = v;
    }
    
    void bendin_01_value_set(number v) {
        this->bendin_01_value = v;
        this->p_04_in1_number_set(v);
    }
    
    void bendin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (status == 224) {
            this->bendin_01_channel_set(channel);
            number amount = data[1] | data[2] << 7;
            number scaledvalue = amount / 16384.;
    
            switch (this->bendin_01_bendmode) {
            case 0:
                {
                this->bendin_01_value_set(int(amount / 128.));
                break;
                }
            case 1:
                {
                this->bendin_01_value_set((scaledvalue - .5) * 2.);
                break;
                }
            case 2:
                {
                this->bendin_01_value_set(amount - 8192);
                break;
                }
            default:
                {
                break;
                }
            }
        }
    }
    
    void p_07_in1_number_set(number v) {
        this->p_07->updateTime(this->_currentTime);
        this->p_07->eventinlet_25_out1_number_set(v);
    }
    
    void p_06_in1_number_set(number v) {
        this->p_06->updateTime(this->_currentTime);
        this->p_06->eventinlet_20_out1_number_set(v);
    }
    
    void midiin_02_midiout_set(number v) {
        this->p_07_in1_number_set(v);
        this->p_06_in1_number_set(v);
    }
    
    void midiin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(port);
        RNBO_UNUSED(channel);
        RNBO_UNUSED(status);
        Index i;
    
        for (i = 0; i < length; i++) {
            this->midiin_02_midiout_set(data[i]);
        }
    }
    
    void bendin_02_channel_set(number v) {
        this->bendin_02_channel = v;
    }
    
    void bendin_02_value_set(number v) {
        this->bendin_02_value = v;
        this->p_06_in1_number_set(v);
    }
    
    void bendin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (status == 224) {
            this->bendin_02_channel_set(channel);
            number amount = data[1] | data[2] << 7;
            number scaledvalue = amount / 16384.;
    
            switch (this->bendin_02_bendmode) {
            case 0:
                {
                this->bendin_02_value_set(int(amount / 128.));
                break;
                }
            case 1:
                {
                this->bendin_02_value_set((scaledvalue - .5) * 2.);
                break;
                }
            case 2:
                {
                this->bendin_02_value_set(amount - 8192);
                break;
                }
            default:
                {
                break;
                }
            }
        }
    }
    
    void midiouthelper_midiout_set(number ) {}
    
    void p_04_perform(SampleValue * out1, Index n) {
        // subpatcher: OscillatorI
        SampleArray<1> outs = {out1};
    
        this->p_04->process(nullptr, 0, outs, 1, n);
    }
    
    void p_05_perform(SampleValue * out1, Index n) {
        // subpatcher: EnvelopeI
        SampleArray<1> outs = {out1};
    
        this->p_05->process(nullptr, 0, outs, 1, n);
    }
    
    void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void onepole_tilde_01_perform(const Sample * x, number freqInHz, SampleValue * out1, Index n) {
        auto __onepole_tilde_01_lastY = this->onepole_tilde_01_lastY;
        auto __onepole_tilde_01_b1 = this->onepole_tilde_01_b1;
        auto __onepole_tilde_01_a0 = this->onepole_tilde_01_a0;
        auto __onepole_tilde_01_needsUpdate = this->onepole_tilde_01_needsUpdate;
        auto __onepole_tilde_01_freq = this->onepole_tilde_01_freq;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (__onepole_tilde_01_freq != freqInHz || (bool)(__onepole_tilde_01_needsUpdate)) {
                __onepole_tilde_01_freq = freqInHz;
                __onepole_tilde_01_a0 = 1 - rnbo_exp(-6.28318530717958647692 * freqInHz / this->sr);
                __onepole_tilde_01_a0 = (__onepole_tilde_01_a0 > 0.99999 ? 0.99999 : (__onepole_tilde_01_a0 < 0.00001 ? 0.00001 : __onepole_tilde_01_a0));
                __onepole_tilde_01_b1 = 1 - __onepole_tilde_01_a0;
                __onepole_tilde_01_needsUpdate = false;
            }
    
            __onepole_tilde_01_lastY = __onepole_tilde_01_a0 * x[(Index)i] + __onepole_tilde_01_b1 * __onepole_tilde_01_lastY;
            out1[(Index)i] = __onepole_tilde_01_lastY;
        }
    
        this->onepole_tilde_01_freq = __onepole_tilde_01_freq;
        this->onepole_tilde_01_needsUpdate = __onepole_tilde_01_needsUpdate;
        this->onepole_tilde_01_a0 = __onepole_tilde_01_a0;
        this->onepole_tilde_01_b1 = __onepole_tilde_01_b1;
        this->onepole_tilde_01_lastY = __onepole_tilde_01_lastY;
    }
    
    void p_06_perform(SampleValue * out1, Index n) {
        // subpatcher: OscillatorII
        SampleArray<1> outs = {out1};
    
        this->p_06->process(nullptr, 0, outs, 1, n);
    }
    
    void p_07_perform(SampleValue * out1, Index n) {
        // subpatcher: EnvelopeII
        SampleArray<1> outs = {out1};
    
        this->p_07->process(nullptr, 0, outs, 1, n);
    }
    
    void dspexpr_06_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void onepole_tilde_02_perform(const Sample * x, number freqInHz, SampleValue * out1, Index n) {
        auto __onepole_tilde_02_lastY = this->onepole_tilde_02_lastY;
        auto __onepole_tilde_02_b1 = this->onepole_tilde_02_b1;
        auto __onepole_tilde_02_a0 = this->onepole_tilde_02_a0;
        auto __onepole_tilde_02_needsUpdate = this->onepole_tilde_02_needsUpdate;
        auto __onepole_tilde_02_freq = this->onepole_tilde_02_freq;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (__onepole_tilde_02_freq != freqInHz || (bool)(__onepole_tilde_02_needsUpdate)) {
                __onepole_tilde_02_freq = freqInHz;
                __onepole_tilde_02_a0 = 1 - rnbo_exp(-6.28318530717958647692 * freqInHz / this->sr);
                __onepole_tilde_02_a0 = (__onepole_tilde_02_a0 > 0.99999 ? 0.99999 : (__onepole_tilde_02_a0 < 0.00001 ? 0.00001 : __onepole_tilde_02_a0));
                __onepole_tilde_02_b1 = 1 - __onepole_tilde_02_a0;
                __onepole_tilde_02_needsUpdate = false;
            }
    
            __onepole_tilde_02_lastY = __onepole_tilde_02_a0 * x[(Index)i] + __onepole_tilde_02_b1 * __onepole_tilde_02_lastY;
            out1[(Index)i] = __onepole_tilde_02_lastY;
        }
    
        this->onepole_tilde_02_freq = __onepole_tilde_02_freq;
        this->onepole_tilde_02_needsUpdate = __onepole_tilde_02_needsUpdate;
        this->onepole_tilde_02_a0 = __onepole_tilde_02_a0;
        this->onepole_tilde_02_b1 = __onepole_tilde_02_b1;
        this->onepole_tilde_02_lastY = __onepole_tilde_02_lastY;
    }
    
    void p_03_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        // subpatcher: Output
        ConstSampleArray<2> ins = {in1, in2};
    
        SampleArray<2> outs = {out1, out2};
        this->p_03->process(ins, 2, outs, 2, n);
    }
    
    void signaladder_01_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signaladder_02_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void onepole_tilde_01_reset() {
        this->onepole_tilde_01_lastY = 0;
        this->onepole_tilde_01_a0 = 0;
        this->onepole_tilde_01_b1 = 0;
    }
    
    void onepole_tilde_01_dspsetup(bool force) {
        if ((bool)(this->onepole_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->onepole_tilde_01_needsUpdate = true;
        this->onepole_tilde_01_reset();
        this->onepole_tilde_01_setupDone = true;
    }
    
    void param_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_01_value;
    }
    
    void param_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_01_value_set(preset["value"]);
    }
    
    void param_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_02_value;
    }
    
    void param_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_02_value_set(preset["value"]);
    }
    
    void param_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_03_value;
    }
    
    void param_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_03_value_set(preset["value"]);
    }
    
    void param_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_04_value;
    }
    
    void param_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_04_value_set(preset["value"]);
    }
    
    void param_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_05_value;
    }
    
    void param_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_05_value_set(preset["value"]);
    }
    
    void param_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_06_value;
    }
    
    void param_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_06_value_set(preset["value"]);
    }
    
    void param_07_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_07_value;
    }
    
    void param_07_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_07_value_set(preset["value"]);
    }
    
    void param_08_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_08_value;
    }
    
    void param_08_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_08_value_set(preset["value"]);
    }
    
    void param_09_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_09_value;
    }
    
    void param_09_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_09_value_set(preset["value"]);
    }
    
    void param_10_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_10_value;
    }
    
    void param_10_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_10_value_set(preset["value"]);
    }
    
    void param_11_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_11_value;
    }
    
    void param_11_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_11_value_set(preset["value"]);
    }
    
    void onepole_tilde_02_reset() {
        this->onepole_tilde_02_lastY = 0;
        this->onepole_tilde_02_a0 = 0;
        this->onepole_tilde_02_b1 = 0;
    }
    
    void onepole_tilde_02_dspsetup(bool force) {
        if ((bool)(this->onepole_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->onepole_tilde_02_needsUpdate = true;
        this->onepole_tilde_02_reset();
        this->onepole_tilde_02_setupDone = true;
    }
    
    void param_12_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_12_value;
    }
    
    void param_12_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_12_value_set(preset["value"]);
    }
    
    void param_13_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_13_value;
    }
    
    void param_13_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_13_value_set(preset["value"]);
    }
    
    void param_14_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_14_value;
    }
    
    void param_14_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_14_value_set(preset["value"]);
    }
    
    void param_15_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_15_value;
    }
    
    void param_15_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_15_value_set(preset["value"]);
    }
    
    void param_16_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_16_value;
    }
    
    void param_16_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_16_value_set(preset["value"]);
    }
    
    void param_17_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_17_value;
    }
    
    void param_17_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_17_value_set(preset["value"]);
    }
    
    void param_18_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_18_value;
    }
    
    void param_18_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_18_value_set(preset["value"]);
    }
    
    void param_19_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_19_value;
    }
    
    void param_19_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_19_value_set(preset["value"]);
    }
    
    void midiouthelper_sendMidi(number v) {
        this->midiouthelper_midiout_set(v);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        midiin_01_port = 0;
        p_03_target = 0;
        onepole_tilde_01_x = 0;
        onepole_tilde_01_freqInHz = 1;
        dspexpr_05_in1 = 0;
        dspexpr_05_in2 = 0;
        p_04_target = 0;
        bendin_01_bendmode = 0;
        bendin_01_value = 0;
        bendin_01_channel = 0;
        bendin_01_input = 0;
        param_01_value = 1;
        param_02_value = 0;
        param_03_value = 0;
        param_04_value = 2;
        param_05_value = 20000;
        param_06_value = 5;
        p_05_target = 0;
        param_07_value = 50;
        param_08_value = 0.5;
        param_09_value = 50;
        param_10_value = 0.3;
        midiin_02_port = 0;
        bendin_02_bendmode = 0;
        bendin_02_value = 0;
        bendin_02_channel = 0;
        bendin_02_input = 0;
        p_06_target = 0;
        param_11_value = 0;
        onepole_tilde_02_x = 0;
        onepole_tilde_02_freqInHz = 1;
        dspexpr_06_in1 = 0;
        dspexpr_06_in2 = 0;
        param_12_value = 0;
        param_13_value = 2;
        param_14_value = 20000;
        param_15_value = 5;
        p_07_target = 0;
        param_16_value = 50;
        param_17_value = 0.5;
        param_18_value = 50;
        param_19_value = 0.3;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        onepole_tilde_01_freq = 0;
        onepole_tilde_01_needsUpdate = false;
        onepole_tilde_01_lastY = 0;
        onepole_tilde_01_a0 = 0;
        onepole_tilde_01_b1 = 0;
        onepole_tilde_01_setupDone = false;
        bendin_01_status = 0;
        bendin_01_byte1 = -1;
        bendin_01_inchan = 0;
        param_01_lastValue = 0;
        param_02_lastValue = 0;
        param_03_lastValue = 0;
        param_04_lastValue = 0;
        param_05_lastValue = 0;
        param_06_lastValue = 0;
        param_07_lastValue = 0;
        param_08_lastValue = 0;
        param_09_lastValue = 0;
        param_10_lastValue = 0;
        bendin_02_status = 0;
        bendin_02_byte1 = -1;
        bendin_02_inchan = 0;
        param_11_lastValue = 0;
        onepole_tilde_02_freq = 0;
        onepole_tilde_02_needsUpdate = false;
        onepole_tilde_02_lastY = 0;
        onepole_tilde_02_a0 = 0;
        onepole_tilde_02_b1 = 0;
        onepole_tilde_02_setupDone = false;
        param_12_lastValue = 0;
        param_13_lastValue = 0;
        param_14_lastValue = 0;
        param_15_lastValue = 0;
        param_16_lastValue = 0;
        param_17_lastValue = 0;
        param_18_lastValue = 0;
        param_19_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number midiin_01_port;
        number p_03_target;
        number onepole_tilde_01_x;
        number onepole_tilde_01_freqInHz;
        number dspexpr_05_in1;
        number dspexpr_05_in2;
        number p_04_target;
        Int bendin_01_bendmode;
        number bendin_01_value;
        number bendin_01_channel;
        number bendin_01_input;
        number param_01_value;
        number param_02_value;
        number param_03_value;
        number param_04_value;
        number param_05_value;
        number param_06_value;
        number p_05_target;
        number param_07_value;
        number param_08_value;
        number param_09_value;
        number param_10_value;
        number midiin_02_port;
        Int bendin_02_bendmode;
        number bendin_02_value;
        number bendin_02_channel;
        number bendin_02_input;
        number p_06_target;
        number param_11_value;
        number onepole_tilde_02_x;
        number onepole_tilde_02_freqInHz;
        number dspexpr_06_in1;
        number dspexpr_06_in2;
        number param_12_value;
        number param_13_value;
        number param_14_value;
        number param_15_value;
        number p_07_target;
        number param_16_value;
        number param_17_value;
        number param_18_value;
        number param_19_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[4];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number onepole_tilde_01_freq;
        bool onepole_tilde_01_needsUpdate;
        number onepole_tilde_01_lastY;
        number onepole_tilde_01_a0;
        number onepole_tilde_01_b1;
        bool onepole_tilde_01_setupDone;
        int bendin_01_status;
        int bendin_01_byte1;
        int bendin_01_inchan;
        number param_01_lastValue;
        number param_02_lastValue;
        number param_03_lastValue;
        number param_04_lastValue;
        number param_05_lastValue;
        number param_06_lastValue;
        number param_07_lastValue;
        number param_08_lastValue;
        number param_09_lastValue;
        number param_10_lastValue;
        int bendin_02_status;
        int bendin_02_byte1;
        int bendin_02_inchan;
        number param_11_lastValue;
        number onepole_tilde_02_freq;
        bool onepole_tilde_02_needsUpdate;
        number onepole_tilde_02_lastY;
        number onepole_tilde_02_a0;
        number onepole_tilde_02_b1;
        bool onepole_tilde_02_setupDone;
        number param_12_lastValue;
        number param_13_lastValue;
        number param_14_lastValue;
        number param_15_lastValue;
        number param_16_lastValue;
        number param_17_lastValue;
        number param_18_lastValue;
        number param_19_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_27* p_03;
        RNBOSubpatcher_28* p_04;
        RNBOSubpatcher_29* p_05;
        RNBOSubpatcher_30* p_06;
        RNBOSubpatcher_31* p_07;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    for (int i = 0; i < 8; i++) {
        delete poly[i];
    }
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->midiin_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 1;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    this->poly_perform(out1, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->globaltransport_dspsetup(forceDSPSetup);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 1;
}

void fillRNBODefaultSinus(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 0:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    }
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processDataViewUpdate(index, time);
    }
}

void initialize() {
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultSinus->setIndex(0);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    for (Index i = 0; i < 8; i++) {
        this->poly[(Index)i] = new RNBOSubpatcher_32();
        this->poly[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->poly[(Index)i]->initialize();
        this->poly[(Index)i]->setParameterOffset(this->getParameterOffset(this->poly[0]));
        this->poly[(Index)i]->setVoiceIndex(i + 1);
    }
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_20_getPresetValue(getSubState(preset, "ModulationMode"));
    this->param_21_getPresetValue(getSubState(preset, "WaveformI"));
    this->param_22_getPresetValue(getSubState(preset, "CoarseI"));
    this->param_23_getPresetValue(getSubState(preset, "BendRangeI"));
    this->param_24_getPresetValue(getSubState(preset, "FilterICutOff"));
    this->param_25_getPresetValue(getSubState(preset, "EnvIAttack"));
    this->param_26_getPresetValue(getSubState(preset, "EnvIDecay"));
    this->param_27_getPresetValue(getSubState(preset, "EnvISustain"));
    this->param_28_getPresetValue(getSubState(preset, "EnvIRelease"));
    this->param_29_getPresetValue(getSubState(preset, "VolumeI"));
    this->param_30_getPresetValue(getSubState(preset, "WaveformII"));
    this->param_31_getPresetValue(getSubState(preset, "CoarseII"));
    this->param_32_getPresetValue(getSubState(preset, "BendRangeII"));
    this->param_33_getPresetValue(getSubState(preset, "FilterIICutOff"));
    this->param_34_getPresetValue(getSubState(preset, "EnvIIAttack"));
    this->param_35_getPresetValue(getSubState(preset, "EnvIIDecay"));
    this->param_36_getPresetValue(getSubState(preset, "EnvIISustain"));
    this->param_37_getPresetValue(getSubState(preset, "EnvIIRelease"));
    this->param_38_getPresetValue(getSubState(preset, "VolumeII"));

    for (Index i = 0; i < 8; i++)
        this->poly[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "poly", i));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_20_setPresetValue(getSubState(preset, "ModulationMode"));
    this->param_21_setPresetValue(getSubState(preset, "WaveformI"));
    this->param_22_setPresetValue(getSubState(preset, "CoarseI"));
    this->param_23_setPresetValue(getSubState(preset, "BendRangeI"));
    this->param_24_setPresetValue(getSubState(preset, "FilterICutOff"));
    this->param_25_setPresetValue(getSubState(preset, "EnvIAttack"));
    this->param_26_setPresetValue(getSubState(preset, "EnvIDecay"));
    this->param_27_setPresetValue(getSubState(preset, "EnvISustain"));
    this->param_28_setPresetValue(getSubState(preset, "EnvIRelease"));
    this->param_29_setPresetValue(getSubState(preset, "VolumeI"));
    this->param_30_setPresetValue(getSubState(preset, "WaveformII"));
    this->param_31_setPresetValue(getSubState(preset, "CoarseII"));
    this->param_32_setPresetValue(getSubState(preset, "BendRangeII"));
    this->param_33_setPresetValue(getSubState(preset, "FilterIICutOff"));
    this->param_34_setPresetValue(getSubState(preset, "EnvIIAttack"));
    this->param_35_setPresetValue(getSubState(preset, "EnvIIDecay"));
    this->param_36_setPresetValue(getSubState(preset, "EnvIISustain"));
    this->param_37_setPresetValue(getSubState(preset, "EnvIIRelease"));
    this->param_38_setPresetValue(getSubState(preset, "VolumeII"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_20_value_set(v);
        break;
        }
    case 1:
        {
        this->param_21_value_set(v);
        break;
        }
    case 2:
        {
        this->param_22_value_set(v);
        break;
        }
    case 3:
        {
        this->param_23_value_set(v);
        break;
        }
    case 4:
        {
        this->param_24_value_set(v);
        break;
        }
    case 5:
        {
        this->param_25_value_set(v);
        break;
        }
    case 6:
        {
        this->param_26_value_set(v);
        break;
        }
    case 7:
        {
        this->param_27_value_set(v);
        break;
        }
    case 8:
        {
        this->param_28_value_set(v);
        break;
        }
    case 9:
        {
        this->param_29_value_set(v);
        break;
        }
    case 10:
        {
        this->param_30_value_set(v);
        break;
        }
    case 11:
        {
        this->param_31_value_set(v);
        break;
        }
    case 12:
        {
        this->param_32_value_set(v);
        break;
        }
    case 13:
        {
        this->param_33_value_set(v);
        break;
        }
    case 14:
        {
        this->param_34_value_set(v);
        break;
        }
    case 15:
        {
        this->param_35_value_set(v);
        break;
        }
    case 16:
        {
        this->param_36_value_set(v);
        break;
        }
    case 17:
        {
        this->param_37_value_set(v);
        break;
        }
    case 18:
        {
        this->param_38_value_set(v);
        break;
        }
    default:
        {
        index -= 19;

        if (index < this->poly[0]->getNumParameters())
            this->poly[0]->setPolyParameterValue((PatcherInterface**)this->poly, index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_20_value;
        }
    case 1:
        {
        return this->param_21_value;
        }
    case 2:
        {
        return this->param_22_value;
        }
    case 3:
        {
        return this->param_23_value;
        }
    case 4:
        {
        return this->param_24_value;
        }
    case 5:
        {
        return this->param_25_value;
        }
    case 6:
        {
        return this->param_26_value;
        }
    case 7:
        {
        return this->param_27_value;
        }
    case 8:
        {
        return this->param_28_value;
        }
    case 9:
        {
        return this->param_29_value;
        }
    case 10:
        {
        return this->param_30_value;
        }
    case 11:
        {
        return this->param_31_value;
        }
    case 12:
        {
        return this->param_32_value;
        }
    case 13:
        {
        return this->param_33_value;
        }
    case 14:
        {
        return this->param_34_value;
        }
    case 15:
        {
        return this->param_35_value;
        }
    case 16:
        {
        return this->param_36_value;
        }
    case 17:
        {
        return this->param_37_value;
        }
    case 18:
        {
        return this->param_38_value;
        }
    default:
        {
        index -= 19;

        if (index < this->poly[0]->getNumParameters())
            return this->poly[0]->getPolyParameterValue((PatcherInterface**)this->poly, index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 19 + this->poly[0]->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "ModulationMode";
        }
    case 1:
        {
        return "WaveformI";
        }
    case 2:
        {
        return "CoarseI";
        }
    case 3:
        {
        return "BendRangeI";
        }
    case 4:
        {
        return "FilterICutOff";
        }
    case 5:
        {
        return "EnvIAttack";
        }
    case 6:
        {
        return "EnvIDecay";
        }
    case 7:
        {
        return "EnvISustain";
        }
    case 8:
        {
        return "EnvIRelease";
        }
    case 9:
        {
        return "VolumeI";
        }
    case 10:
        {
        return "WaveformII";
        }
    case 11:
        {
        return "CoarseII";
        }
    case 12:
        {
        return "BendRangeII";
        }
    case 13:
        {
        return "FilterIICutOff";
        }
    case 14:
        {
        return "EnvIIAttack";
        }
    case 15:
        {
        return "EnvIIDecay";
        }
    case 16:
        {
        return "EnvIISustain";
        }
    case 17:
        {
        return "EnvIIRelease";
        }
    case 18:
        {
        return "VolumeII";
        }
    default:
        {
        index -= 19;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterName(index);
            }
        }

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "ModulationMode";
        }
    case 1:
        {
        return "WaveformI";
        }
    case 2:
        {
        return "CoarseI";
        }
    case 3:
        {
        return "BendRangeI";
        }
    case 4:
        {
        return "FilterICutOff";
        }
    case 5:
        {
        return "EnvIAttack";
        }
    case 6:
        {
        return "EnvIDecay";
        }
    case 7:
        {
        return "EnvISustain";
        }
    case 8:
        {
        return "EnvIRelease";
        }
    case 9:
        {
        return "VolumeI";
        }
    case 10:
        {
        return "WaveformII";
        }
    case 11:
        {
        return "CoarseII";
        }
    case 12:
        {
        return "BendRangeII";
        }
    case 13:
        {
        return "FilterIICutOff";
        }
    case 14:
        {
        return "EnvIIAttack";
        }
    case 15:
        {
        return "EnvIIDecay";
        }
    case 16:
        {
        return "EnvIISustain";
        }
    case 17:
        {
        return "EnvIIRelease";
        }
    case 18:
        {
        return "VolumeII";
        }
    default:
        {
        index -= 19;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterId(index);
            }
        }

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 1;
            info->max = 2;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 4;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -44;
            info->max = 44;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 2;
            info->min = -22;
            info->max = 22;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 20000;
            info->min = 10;
            info->max = 20000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 5;
            info->min = 1;
            info->max = 20000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 1;
            info->max = 20000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 1;
            info->max = 20000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.3;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 4;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 11:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -44;
            info->max = 44;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 12:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 2;
            info->min = -22;
            info->max = 22;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 13:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 20000;
            info->min = 10;
            info->max = 20000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 14:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 5;
            info->min = 1;
            info->max = 20000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 15:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 1;
            info->max = 20000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 16:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 17:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 1;
            info->max = 20000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 18:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.3;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 19;

            if (index < this->poly[0]->getNumParameters()) {
                for (Index i = 0; i < 8; i++) {
                    this->poly[i]->getParameterInfo(index, info);
                }
            }

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->poly[0])
        return 19;

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 7:
    case 9:
    case 16:
    case 18:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 1:
    case 10:
        {
        {
            value = (value < 0 ? 0 : (value > 4 ? 4 : value));
            ParameterValue normalizedValue = (value - 0) / (4 - 0);
            return normalizedValue;
        }
        }
    case 0:
        {
        {
            value = (value < 1 ? 1 : (value > 2 ? 2 : value));
            ParameterValue normalizedValue = (value - 1) / (2 - 1);
            return normalizedValue;
        }
        }
    case 5:
    case 6:
    case 8:
    case 14:
    case 15:
    case 17:
        {
        {
            value = (value < 1 ? 1 : (value > 20000 ? 20000 : value));
            ParameterValue normalizedValue = (value - 1) / (20000 - 1);
            return normalizedValue;
        }
        }
    case 4:
    case 13:
        {
        {
            value = (value < 10 ? 10 : (value > 20000 ? 20000 : value));
            ParameterValue normalizedValue = (value - 10) / (20000 - 10);
            return normalizedValue;
        }
        }
    case 2:
    case 11:
        {
        {
            value = (value < -44 ? -44 : (value > 44 ? 44 : value));
            ParameterValue normalizedValue = (value - -44) / (44 - -44);
            return normalizedValue;
        }
        }
    case 3:
    case 12:
        {
        {
            value = (value < -22 ? -22 : (value > 22 ? 22 : value));
            ParameterValue normalizedValue = (value - -22) / (22 - -22);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 19;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 7:
    case 9:
    case 16:
    case 18:
        {
        {
            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 1:
    case 10:
        {
        {
            {
                return 0 + value * (4 - 0);
            }
        }
        }
    case 0:
        {
        {
            {
                return 1 + value * (2 - 1);
            }
        }
        }
    case 5:
    case 6:
    case 8:
    case 14:
    case 15:
    case 17:
        {
        {
            {
                return 1 + value * (20000 - 1);
            }
        }
        }
    case 4:
    case 13:
        {
        {
            {
                return 10 + value * (20000 - 10);
            }
        }
        }
    case 2:
    case 11:
        {
        {
            {
                return -44 + value * (44 - -44);
            }
        }
        }
    case 3:
    case 12:
        {
        {
            {
                return -22 + value * (22 - -22);
            }
        }
        }
    default:
        {
        index -= 19;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_20_value_constrain(value);
        }
    case 1:
        {
        return this->param_21_value_constrain(value);
        }
    case 2:
        {
        return this->param_22_value_constrain(value);
        }
    case 3:
        {
        return this->param_23_value_constrain(value);
        }
    case 4:
        {
        return this->param_24_value_constrain(value);
        }
    case 5:
        {
        return this->param_25_value_constrain(value);
        }
    case 6:
        {
        return this->param_26_value_constrain(value);
        }
    case 7:
        {
        return this->param_27_value_constrain(value);
        }
    case 8:
        {
        return this->param_28_value_constrain(value);
        }
    case 9:
        {
        return this->param_29_value_constrain(value);
        }
    case 10:
        {
        return this->param_30_value_constrain(value);
        }
    case 11:
        {
        return this->param_31_value_constrain(value);
        }
    case 12:
        {
        return this->param_32_value_constrain(value);
        }
    case 13:
        {
        return this->param_33_value_constrain(value);
        }
    case 14:
        {
        return this->param_34_value_constrain(value);
        }
    case 15:
        {
        return this->param_35_value_constrain(value);
        }
    case 16:
        {
        return this->param_36_value_constrain(value);
        }
    case 17:
        {
        return this->param_37_value_constrain(value);
        }
    case 18:
        {
        return this->param_38_value_constrain(value);
        }
    default:
        {
        index -= 19;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->constrainParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processNumMessage(tag, objectId, time, payload);
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processListMessage(tag, objectId, time, payload);
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processBangMessage(tag, objectId, time);
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    auto subpatchResult_0 = this->poly[0]->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

void param_20_value_set(number v) {
    v = this->param_20_value_constrain(v);
    this->param_20_value = v;
    this->sendParameter(0, false);

    if (this->param_20_value != this->param_20_lastValue) {
        this->getEngine()->presetTouched();
        this->param_20_lastValue = this->param_20_value;
    }

    this->poly_ModulationMode_set(v);
}

void param_21_value_set(number v) {
    v = this->param_21_value_constrain(v);
    this->param_21_value = v;
    this->sendParameter(1, false);

    if (this->param_21_value != this->param_21_lastValue) {
        this->getEngine()->presetTouched();
        this->param_21_lastValue = this->param_21_value;
    }

    this->poly_WaveformI_set(v);
}

void param_22_value_set(number v) {
    v = this->param_22_value_constrain(v);
    this->param_22_value = v;
    this->sendParameter(2, false);

    if (this->param_22_value != this->param_22_lastValue) {
        this->getEngine()->presetTouched();
        this->param_22_lastValue = this->param_22_value;
    }

    this->poly_CoarseI_set(v);
}

void param_23_value_set(number v) {
    v = this->param_23_value_constrain(v);
    this->param_23_value = v;
    this->sendParameter(3, false);

    if (this->param_23_value != this->param_23_lastValue) {
        this->getEngine()->presetTouched();
        this->param_23_lastValue = this->param_23_value;
    }

    this->poly_BendRangeI_set(v);
}

void param_24_value_set(number v) {
    v = this->param_24_value_constrain(v);
    this->param_24_value = v;
    this->sendParameter(4, false);

    if (this->param_24_value != this->param_24_lastValue) {
        this->getEngine()->presetTouched();
        this->param_24_lastValue = this->param_24_value;
    }

    this->poly_FilterICutOff_set(v);
}

void param_25_value_set(number v) {
    v = this->param_25_value_constrain(v);
    this->param_25_value = v;
    this->sendParameter(5, false);

    if (this->param_25_value != this->param_25_lastValue) {
        this->getEngine()->presetTouched();
        this->param_25_lastValue = this->param_25_value;
    }

    this->poly_EnvIAttack_set(v);
}

void param_26_value_set(number v) {
    v = this->param_26_value_constrain(v);
    this->param_26_value = v;
    this->sendParameter(6, false);

    if (this->param_26_value != this->param_26_lastValue) {
        this->getEngine()->presetTouched();
        this->param_26_lastValue = this->param_26_value;
    }

    this->poly_EnvIDecay_set(v);
}

void param_27_value_set(number v) {
    v = this->param_27_value_constrain(v);
    this->param_27_value = v;
    this->sendParameter(7, false);

    if (this->param_27_value != this->param_27_lastValue) {
        this->getEngine()->presetTouched();
        this->param_27_lastValue = this->param_27_value;
    }

    this->poly_EnvISustain_set(v);
}

void param_28_value_set(number v) {
    v = this->param_28_value_constrain(v);
    this->param_28_value = v;
    this->sendParameter(8, false);

    if (this->param_28_value != this->param_28_lastValue) {
        this->getEngine()->presetTouched();
        this->param_28_lastValue = this->param_28_value;
    }

    this->poly_EnvIRelease_set(v);
}

void param_29_value_set(number v) {
    v = this->param_29_value_constrain(v);
    this->param_29_value = v;
    this->sendParameter(9, false);

    if (this->param_29_value != this->param_29_lastValue) {
        this->getEngine()->presetTouched();
        this->param_29_lastValue = this->param_29_value;
    }

    this->poly_VolumeI_set(v);
}

void param_30_value_set(number v) {
    v = this->param_30_value_constrain(v);
    this->param_30_value = v;
    this->sendParameter(10, false);

    if (this->param_30_value != this->param_30_lastValue) {
        this->getEngine()->presetTouched();
        this->param_30_lastValue = this->param_30_value;
    }

    this->poly_WaveformII_set(v);
}

void param_31_value_set(number v) {
    v = this->param_31_value_constrain(v);
    this->param_31_value = v;
    this->sendParameter(11, false);

    if (this->param_31_value != this->param_31_lastValue) {
        this->getEngine()->presetTouched();
        this->param_31_lastValue = this->param_31_value;
    }

    this->poly_CoarseII_set(v);
}

void param_32_value_set(number v) {
    v = this->param_32_value_constrain(v);
    this->param_32_value = v;
    this->sendParameter(12, false);

    if (this->param_32_value != this->param_32_lastValue) {
        this->getEngine()->presetTouched();
        this->param_32_lastValue = this->param_32_value;
    }

    this->poly_BendRangeII_set(v);
}

void param_33_value_set(number v) {
    v = this->param_33_value_constrain(v);
    this->param_33_value = v;
    this->sendParameter(13, false);

    if (this->param_33_value != this->param_33_lastValue) {
        this->getEngine()->presetTouched();
        this->param_33_lastValue = this->param_33_value;
    }

    this->poly_FilterIICutOff_set(v);
}

void param_34_value_set(number v) {
    v = this->param_34_value_constrain(v);
    this->param_34_value = v;
    this->sendParameter(14, false);

    if (this->param_34_value != this->param_34_lastValue) {
        this->getEngine()->presetTouched();
        this->param_34_lastValue = this->param_34_value;
    }

    this->poly_EnvIIAttack_set(v);
}

void param_35_value_set(number v) {
    v = this->param_35_value_constrain(v);
    this->param_35_value = v;
    this->sendParameter(15, false);

    if (this->param_35_value != this->param_35_lastValue) {
        this->getEngine()->presetTouched();
        this->param_35_lastValue = this->param_35_value;
    }

    this->poly_EnvIIDecay_set(v);
}

void param_36_value_set(number v) {
    v = this->param_36_value_constrain(v);
    this->param_36_value = v;
    this->sendParameter(16, false);

    if (this->param_36_value != this->param_36_lastValue) {
        this->getEngine()->presetTouched();
        this->param_36_lastValue = this->param_36_value;
    }

    this->poly_EnvIISustain_set(v);
}

void param_37_value_set(number v) {
    v = this->param_37_value_constrain(v);
    this->param_37_value = v;
    this->sendParameter(17, false);

    if (this->param_37_value != this->param_37_lastValue) {
        this->getEngine()->presetTouched();
        this->param_37_lastValue = this->param_37_value;
    }

    this->poly_EnvIIRelease_set(v);
}

void param_38_value_set(number v) {
    v = this->param_38_value_constrain(v);
    this->param_38_value = v;
    this->sendParameter(18, false);

    if (this->param_38_value != this->param_38_lastValue) {
        this->getEngine()->presetTouched();
        this->param_38_lastValue = this->param_38_value;
    }

    this->poly_VolumeII_set(v);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    for (Index i = 0; i < 8; i++) {
        this->poly[i]->allocateDataRefs();
    }

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->midinotecontroller_01_init();

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->initializeObjects();
    }
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->startup();
    }

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 0);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    {
        this->scheduleParamInit(11, 0);
    }

    {
        this->scheduleParamInit(12, 0);
    }

    {
        this->scheduleParamInit(13, 0);
    }

    {
        this->scheduleParamInit(14, 0);
    }

    {
        this->scheduleParamInit(15, 0);
    }

    {
        this->scheduleParamInit(16, 0);
    }

    {
        this->scheduleParamInit(17, 0);
    }

    {
        this->scheduleParamInit(18, 0);
    }

    this->processParamInitEvents();
}

number param_20_value_constrain(number v) const {
    v = (v > 2 ? 2 : (v < 1 ? 1 : v));
    return v;
}

void poly_ModulationMode_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(0, v, this->_currentTime);
        }
    }
}

number param_21_value_constrain(number v) const {
    v = (v > 4 ? 4 : (v < 0 ? 0 : v));
    return v;
}

void poly_WaveformI_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(1, v, this->_currentTime);
        }
    }
}

number param_22_value_constrain(number v) const {
    v = (v > 44 ? 44 : (v < -44 ? -44 : v));
    return v;
}

void poly_CoarseI_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(2, v, this->_currentTime);
        }
    }
}

number param_23_value_constrain(number v) const {
    v = (v > 22 ? 22 : (v < -22 ? -22 : v));
    return v;
}

void poly_BendRangeI_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(3, v, this->_currentTime);
        }
    }
}

number param_24_value_constrain(number v) const {
    v = (v > 20000 ? 20000 : (v < 10 ? 10 : v));
    return v;
}

void poly_FilterICutOff_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(4, v, this->_currentTime);
        }
    }
}

number param_25_value_constrain(number v) const {
    v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
    return v;
}

void poly_EnvIAttack_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(5, v, this->_currentTime);
        }
    }
}

number param_26_value_constrain(number v) const {
    v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
    return v;
}

void poly_EnvIDecay_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(6, v, this->_currentTime);
        }
    }
}

number param_27_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void poly_EnvISustain_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(7, v, this->_currentTime);
        }
    }
}

number param_28_value_constrain(number v) const {
    v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
    return v;
}

void poly_EnvIRelease_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(8, v, this->_currentTime);
        }
    }
}

number param_29_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void poly_VolumeI_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(9, v, this->_currentTime);
        }
    }
}

number param_30_value_constrain(number v) const {
    v = (v > 4 ? 4 : (v < 0 ? 0 : v));
    return v;
}

void poly_WaveformII_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(10, v, this->_currentTime);
        }
    }
}

number param_31_value_constrain(number v) const {
    v = (v > 44 ? 44 : (v < -44 ? -44 : v));
    return v;
}

void poly_CoarseII_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(11, v, this->_currentTime);
        }
    }
}

number param_32_value_constrain(number v) const {
    v = (v > 22 ? 22 : (v < -22 ? -22 : v));
    return v;
}

void poly_BendRangeII_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(12, v, this->_currentTime);
        }
    }
}

number param_33_value_constrain(number v) const {
    v = (v > 20000 ? 20000 : (v < 10 ? 10 : v));
    return v;
}

void poly_FilterIICutOff_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(13, v, this->_currentTime);
        }
    }
}

number param_34_value_constrain(number v) const {
    v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
    return v;
}

void poly_EnvIIAttack_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(14, v, this->_currentTime);
        }
    }
}

number param_35_value_constrain(number v) const {
    v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
    return v;
}

void poly_EnvIIDecay_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(15, v, this->_currentTime);
        }
    }
}

number param_36_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void poly_EnvIISustain_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(16, v, this->_currentTime);
        }
    }
}

number param_37_value_constrain(number v) const {
    v = (v > 20000 ? 20000 : (v < 1 ? 1 : v));
    return v;
}

void poly_EnvIIRelease_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(17, v, this->_currentTime);
        }
    }
}

number param_38_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void poly_VolumeII_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(18, v, this->_currentTime);
        }
    }
}

void midinotecontroller_01_currenttarget_set(number v) {
    this->midinotecontroller_01_currenttarget = v;
}

void poly_target_set(number v) {
    this->poly_target = v;
    this->midinotecontroller_01_currenttarget_set(v);
}

void midinotecontroller_01_target_set(number v) {
    this->poly_target_set(v);
}

void poly_midiininternal_set(number v) {
    Index sendlen = 0;
    this->poly_currentStatus = parseMidi(this->poly_currentStatus, (int)(v), this->poly_mididata[0]);

    switch ((int)this->poly_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        this->poly_mididata[0] = (uint8_t)(v);
        this->poly_mididata[1] = 0;
        break;
        }
    case MIDI_SecondByteReceived:
    case MIDI_ProgramChange:
    case MIDI_ChannelPressure:
        {
        this->poly_mididata[1] = (uint8_t)(v);

        if (this->poly_currentStatus == MIDI_ProgramChange || this->poly_currentStatus == MIDI_ChannelPressure) {
            sendlen = 2;
        }

        break;
        }
    case MIDI_NoteOff:
    case MIDI_NoteOn:
    case MIDI_Aftertouch:
    case MIDI_CC:
    case MIDI_PitchBend:
    default:
        {
        this->poly_mididata[2] = (uint8_t)(v);
        sendlen = 3;
        break;
        }
    }

    if (sendlen > 0) {
        number i;

        if (this->poly_target > 0 && this->poly_target <= 8) {
            i = this->poly_target - 1;
            this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
        } else if (this->poly_target == 0) {
            for (i = 0; i < 8; i++) {
                this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
            }
        }
    }
}

void midinotecontroller_01_midiout_set(number v) {
    this->poly_midiininternal_set(v);
}

void poly_noteNumber_set(number v) {
    if (this->poly_target > 0) {
        this->poly[(Index)(this->poly_target - 1)]->setNoteNumber((int)(v));
    }
}

void midinotecontroller_01_noteNumber_set(number v) {
    this->poly_noteNumber_set(v);
}

void midinotecontroller_01_voicestatus_set(const list& v) {
    if (v[1] == 1) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v[0]);
        this->midinotecontroller_01_noteNumber_set(0);
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void poly_voicestatus_set(const list& v) {
    this->midinotecontroller_01_voicestatus_set(v);
}

void poly_activevoices_set(number ) {}

void poly_mute_set(const list& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 8; i++) {
            this->poly[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 8) {
            this->poly[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->poly_voicestatus_set(tmp);
    this->poly_activevoices_set(this->poly_calcActiveVoices());
}

void midinotecontroller_01_mute_set(const list& v) {
    this->poly_mute_set(v);
}

void midinotecontroller_01_midiin_set(number v) {
    this->midinotecontroller_01_midiin = v;
    int val = (int)(v);

    this->midinotecontroller_01_currentStatus = parseMidi(
        this->midinotecontroller_01_currentStatus,
        (int)(v),
        this->midinotecontroller_01_status
    );

    switch ((int)this->midinotecontroller_01_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        {
            this->midinotecontroller_01_status = val;
            this->midinotecontroller_01_byte1 = -1;
            break;
        }
        }
    case MIDI_SecondByteReceived:
        {
        this->midinotecontroller_01_byte1 = val;
        break;
        }
    case MIDI_NoteOn:
        {
        {
            bool sendnoteoff = true;
            number target = 1;
            MillisecondTime oldest = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[0]);
            number target_state = this->midinotecontroller_01_voice_state[0];

            for (Index i = 0; i < 8; i++) {
                number candidate_state = this->midinotecontroller_01_voice_state[(Index)i];

                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == this->midinotecontroller_01_byte1 && candidate_state == MIDI_NoteState_On) {
                    sendnoteoff = false;
                    target = i + 1;
                    break;
                }

                if (i > 0) {
                    if (candidate_state != MIDI_NoteState_On || target_state == MIDI_NoteState_On) {
                        MillisecondTime candidate_ontime = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[(Index)i]);

                        if (candidate_ontime < oldest || (target_state == MIDI_NoteState_On && candidate_state != MIDI_NoteState_On)) {
                            target = i + 1;
                            oldest = candidate_ontime;
                            target_state = candidate_state;
                        }
                    }
                }
            }

            if ((bool)(sendnoteoff))
                this->midinotecontroller_01_sendnoteoff((int)(target));

            int i = (int)(target - 1);
            this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_On;
            this->midinotecontroller_01_voice_lastontime[(Index)i] = this->currenttime();
            this->midinotecontroller_01_voice_notenumber[(Index)i] = this->midinotecontroller_01_byte1;
            this->midinotecontroller_01_voice_channel[(Index)i] = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index j = 0; j < 128; j++) {
                if (this->midinotecontroller_01_notesdown[(Index)j] == 0) {
                    this->midinotecontroller_01_notesdown[(Index)j] = this->midinotecontroller_01_voice_notenumber[(Index)i];
                    break;
                }
            }

            this->midinotecontroller_01_note_lastvelocity[(Index)this->midinotecontroller_01_voice_notenumber[(Index)i]] = val;
            this->midinotecontroller_01_sendpitchbend((int)(i));
            this->midinotecontroller_01_sendpressure((int)(i));
            this->midinotecontroller_01_sendtimbre((int)(i));
            this->midinotecontroller_01_muteval[0] = target;
            this->midinotecontroller_01_muteval[1] = 0;
            this->midinotecontroller_01_mute_set(this->midinotecontroller_01_muteval);
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(target);
            this->midinotecontroller_01_noteNumber_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);

            this->midinotecontroller_01_midiout_set(
                (BinOpInt)((BinOpInt)MIDI_NoteOnMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
            );

            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
            this->midinotecontroller_01_midiout_set(val);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_NoteOff:
        {
        {
            number target = 0;
            number notenumber = this->midinotecontroller_01_byte1;
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == notenumber && this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_On) {
                    target = i + 1;
                    break;
                }
            }

            if (target > 0) {
                int i = (int)(target - 1);
                Index j = (Index)(channel);
                bool ignoresustainchannel = true;

                if ((bool)(this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)])) {
                    this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Sustained;
                } else {
                    number currentTarget = this->midinotecontroller_01_currenttarget;
                    this->midinotecontroller_01_target_set(target);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                    this->midinotecontroller_01_midiout_set(v);
                    this->midinotecontroller_01_target_set(currentTarget);

                    if (this->midinotecontroller_01_currentStatus == MIDI_NoteOff) {
                        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                    }
                }
            } else
                {}

            bool found = false;

            for (Index i = 0; i < 128; i++) {
                if (this->midinotecontroller_01_notesdown[(Index)i] == 0) {
                    break;
                } else if (this->midinotecontroller_01_notesdown[(Index)i] == notenumber) {
                    found = true;
                }

                if ((bool)(found)) {
                    this->midinotecontroller_01_notesdown[(Index)i] = this->midinotecontroller_01_notesdown[(Index)(i + 1)];
                }
            }

            break;
        }
        }
    case MIDI_Aftertouch:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_midiout_set(v);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_CC:
        {
        {
            bool sendToAllVoices = true;

            switch ((int)this->midinotecontroller_01_byte1) {
            case MIDI_CC_Sustain:
                {
                {
                    bool pedaldown = (bool)((val >= 64 ? true : false));
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    Index j = (Index)(channel);
                    bool ignoresustainchannel = true;
                    this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)] = pedaldown;

                    if ((bool)(!(bool)(pedaldown))) {
                        for (Index i = 0; i < 8; i++) {
                            if (((bool)(ignoresustainchannel) || this->midinotecontroller_01_voice_channel[(Index)i] == channel) && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_Sustained) {
                                number currentTarget = this->midinotecontroller_01_currenttarget;
                                this->midinotecontroller_01_target_set(i + 1);
                                this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)j));
                                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
                                this->midinotecontroller_01_midiout_set(64);
                                this->midinotecontroller_01_target_set(currentTarget);
                                this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                            }
                        }
                    }

                    break;
                }
                }
            case MIDI_CC_TimbreMSB:
                {
                {
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    int k = (int)(v);
                    number timbre = (BinOpInt)(((BinOpInt)((BinOpInt)k & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32));
                    this->midinotecontroller_01_channel_timbre[(Index)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F)] = timbre;

                    for (Index i = 0; i < 8; i++) {
                        if (this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
                            this->midinotecontroller_01_sendtimbre(i);
                        }
                    }

                    sendToAllVoices = false;
                    break;
                }
                }
            case MIDI_CC_TimbreLSB:
                {
                {
                    break;
                }
                }
            case MIDI_CC_AllNotesOff:
                {
                {
                    this->midinotecontroller_01_sendallnotesoff();
                    break;
                }
                }
            }

            if ((bool)(sendToAllVoices)) {
                number currentTarget = this->midinotecontroller_01_currenttarget;
                this->midinotecontroller_01_target_set(0);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                this->midinotecontroller_01_midiout_set(v);
                this->midinotecontroller_01_target_set(currentTarget);
            }

            break;
        }
        }
    case MIDI_ProgramChange:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_ChannelPressure:
        {
        {
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (number i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    int k = (int)(channel);
                    this->midinotecontroller_01_channel_pressure[(Index)k] = v;
                    this->midinotecontroller_01_sendpressure(i);
                }
            }

            break;
        }
        }
    case MIDI_PitchBend:
        {
        {
            number bendamount = (BinOpInt)((BinOpInt)this->midinotecontroller_01_byte1 | (BinOpInt)((BinOpInt)val << imod_nocast((UBinOpInt)7, 32)));
            int channel = (int)((BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F));
            this->midinotecontroller_01_channel_pitchbend[(Index)channel] = bendamount;

            for (Index i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    this->midinotecontroller_01_sendpitchbend(i);
                }
            }

            break;
        }
        }
    }
}

void poly_midiin_set(number v) {
    this->poly_midiin = v;
    this->midinotecontroller_01_midiin_set(v);
}

void midiin_midiout_set(number v) {
    this->poly_midiin_set(v);
}

void midiin_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(port);
    RNBO_UNUSED(channel);
    RNBO_UNUSED(status);
    Index i;

    for (i = 0; i < length; i++) {
        this->midiin_midiout_set(data[i]);
    }
}

void poly_perform(SampleValue * out1, SampleValue * out2, Index n) {
    SampleArray<2> outs = {out1, out2};

    for (number chan = 0; chan < 2; chan++)
        zeroSignal(outs[(Index)chan], n);

    for (Index i = 0; i < 8; i++)
        this->poly[(Index)i]->process(nullptr, 0, outs, 2, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void param_20_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_20_value;
}

void param_20_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_20_value_set(preset["value"]);
}

void param_21_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_21_value;
}

void param_21_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_21_value_set(preset["value"]);
}

void param_22_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_22_value;
}

void param_22_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_22_value_set(preset["value"]);
}

void param_23_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_23_value;
}

void param_23_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_23_value_set(preset["value"]);
}

void param_24_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_24_value;
}

void param_24_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_24_value_set(preset["value"]);
}

void param_25_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_25_value;
}

void param_25_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_25_value_set(preset["value"]);
}

void param_26_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_26_value;
}

void param_26_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_26_value_set(preset["value"]);
}

void param_27_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_27_value;
}

void param_27_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_27_value_set(preset["value"]);
}

void param_28_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_28_value;
}

void param_28_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_28_value_set(preset["value"]);
}

void param_29_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_29_value;
}

void param_29_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_29_value_set(preset["value"]);
}

void param_30_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_30_value;
}

void param_30_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_30_value_set(preset["value"]);
}

void param_31_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_31_value;
}

void param_31_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_31_value_set(preset["value"]);
}

void param_32_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_32_value;
}

void param_32_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_32_value_set(preset["value"]);
}

void param_33_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_33_value;
}

void param_33_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_33_value_set(preset["value"]);
}

void param_34_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_34_value;
}

void param_34_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_34_value_set(preset["value"]);
}

void param_35_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_35_value;
}

void param_35_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_35_value_set(preset["value"]);
}

void param_36_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_36_value;
}

void param_36_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_36_value_set(preset["value"]);
}

void param_37_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_37_value;
}

void param_37_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_37_value_set(preset["value"]);
}

void param_38_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_38_value;
}

void param_38_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_38_value_set(preset["value"]);
}

number poly_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 8; i++) {
            if ((bool)(!(bool)(this->poly[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
}

void midinotecontroller_01_init() {
    for (Index i = 0; i < 16; i++) {
        this->midinotecontroller_01_channel_pitchbend[(Index)i] = 0x2000;
    }

    for (Index i = 0; i < 8; i++) {
        this->midinotecontroller_01_voice_lastontime[(Index)i] = -1;
    }
}

void midinotecontroller_01_sendnoteoff(int target) {
    int i = (int)(target - 1);

    if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(target);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
        );

        this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
        this->midinotecontroller_01_midiout_set(64);
        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpitchbend(int v) {
    if (v >= 0 && v < 8) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v + 1);
        int totalbendamount = (int)(this->midinotecontroller_01_channel_pitchbend[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_PitchBendMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
        );

        this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)totalbendamount & (BinOpInt)0x7F));

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)((BinOpInt)totalbendamount >> imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)7, 32), 32)) & (BinOpInt)0x7F)
        );

        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpressure(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_ChannelPressureMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(
        this->midinotecontroller_01_channel_pressure[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendtimbre(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreLSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreMSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] >> imod_nocast((UBinOpInt)7, 32)) & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendallnotesoff() {
    for (Index i = 1; i <= 8; i++) {
        this->midinotecontroller_01_sendnoteoff(i);
    }
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    midiin_port = 0;
    midiout_port = 0;
    param_20_value = 1;
    param_21_value = 0;
    param_22_value = 0;
    param_23_value = 2;
    param_24_value = 20000;
    param_25_value = 5;
    param_26_value = 50;
    param_27_value = 0.5;
    param_28_value = 50;
    param_29_value = 0.3;
    param_30_value = 0;
    param_31_value = 0;
    param_32_value = 2;
    param_33_value = 20000;
    param_34_value = 5;
    param_35_value = 50;
    param_36_value = 0.5;
    param_37_value = 50;
    param_38_value = 0.3;
    poly_target = 0;
    poly_midiin = 0;
    midinotecontroller_01_currenttarget = 0;
    midinotecontroller_01_midiin = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    midiout_currentStatus = -1;
    midiout_status = -1;
    midiout_byte1 = -1;
    param_20_lastValue = 0;
    param_21_lastValue = 0;
    param_22_lastValue = 0;
    param_23_lastValue = 0;
    param_24_lastValue = 0;
    param_25_lastValue = 0;
    param_26_lastValue = 0;
    param_27_lastValue = 0;
    param_28_lastValue = 0;
    param_29_lastValue = 0;
    param_30_lastValue = 0;
    param_31_lastValue = 0;
    param_32_lastValue = 0;
    param_33_lastValue = 0;
    param_34_lastValue = 0;
    param_35_lastValue = 0;
    param_36_lastValue = 0;
    param_37_lastValue = 0;
    param_38_lastValue = 0;
    poly_currentStatus = -1;
    poly_mididata[0] = 0;
    poly_mididata[1] = 0;
    poly_mididata[2] = 0;
    midinotecontroller_01_currentStatus = -1;
    midinotecontroller_01_status = -1;
    midinotecontroller_01_byte1 = -1;
    midinotecontroller_01_zone_masterchannel = 1;
    midinotecontroller_01_zone_numnotechannels = 15;
    midinotecontroller_01_zone_masterpitchbendrange = 2;
    midinotecontroller_01_zone_pernotepitchbendrange = 48;
    midinotecontroller_01_muteval = { 0, 0 };
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number midiin_port;
    number midiout_port;
    number param_20_value;
    number param_21_value;
    number param_22_value;
    number param_23_value;
    number param_24_value;
    number param_25_value;
    number param_26_value;
    number param_27_value;
    number param_28_value;
    number param_29_value;
    number param_30_value;
    number param_31_value;
    number param_32_value;
    number param_33_value;
    number param_34_value;
    number param_35_value;
    number param_36_value;
    number param_37_value;
    number param_38_value;
    number poly_target;
    number poly_midiin;
    number midinotecontroller_01_currenttarget;
    number midinotecontroller_01_midiin;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    int midiout_currentStatus;
    int midiout_status;
    int midiout_byte1;
    list midiout_sysex;
    number param_20_lastValue;
    number param_21_lastValue;
    number param_22_lastValue;
    number param_23_lastValue;
    number param_24_lastValue;
    number param_25_lastValue;
    number param_26_lastValue;
    number param_27_lastValue;
    number param_28_lastValue;
    number param_29_lastValue;
    number param_30_lastValue;
    number param_31_lastValue;
    number param_32_lastValue;
    number param_33_lastValue;
    number param_34_lastValue;
    number param_35_lastValue;
    number param_36_lastValue;
    number param_37_lastValue;
    number param_38_lastValue;
    int poly_currentStatus;
    uint8_t poly_mididata[3];
    int midinotecontroller_01_currentStatus;
    int midinotecontroller_01_status;
    int midinotecontroller_01_byte1;
    int midinotecontroller_01_zone_masterchannel;
    int midinotecontroller_01_zone_numnotechannels;
    int midinotecontroller_01_zone_masterpitchbendrange;
    int midinotecontroller_01_zone_pernotepitchbendrange;
    number midinotecontroller_01_channel_pitchbend[16] = { };
    number midinotecontroller_01_channel_pressure[16] = { };
    number midinotecontroller_01_channel_timbre[16] = { };
    Int midinotecontroller_01_channel_sustain[16] = { };
    MillisecondTime midinotecontroller_01_voice_lastontime[8] = { };
    number midinotecontroller_01_voice_notenumber[8] = { };
    number midinotecontroller_01_voice_channel[8] = { };
    number midinotecontroller_01_voice_state[8] = { };
    number midinotecontroller_01_notesdown[129] = { };
    number midinotecontroller_01_note_lastvelocity[128] = { };
    list midinotecontroller_01_muteval;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef RNBODefaultSinus;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_32* poly[8];

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

