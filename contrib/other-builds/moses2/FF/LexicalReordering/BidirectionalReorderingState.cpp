/*
 * BidirectionalReorderingState.cpp
 *
 *  Created on: 22 Mar 2016
 *      Author: hieu
 */
#include <boost/functional/hash_fwd.hpp>
#include "BidirectionalReorderingState.h"
#include "../../legacy/Util2.h"

using namespace std;

namespace Moses2 {

BidirectionalReorderingState::BidirectionalReorderingState(
		const LRModel &config,
        LRState *bw,
        LRState *fw,
		size_t offset)
: LRState(config,
          LRModel::Bidirectional,
          offset)
, m_backward(bw)
, m_forward(fw)
{}

BidirectionalReorderingState::~BidirectionalReorderingState() {
	// TODO Auto-generated destructor stub
}

void BidirectionalReorderingState::Init(const LRState *prev,
		  const TargetPhrase &topt,
		  const InputPathBase &path,
		  bool first)
{
	if (m_backward) {
		m_backward->Init(prev, topt, path, first);
	}
}

std::string BidirectionalReorderingState::ToString() const
{ return "BidirectionalReorderingState "
		+ SPrint(this) + " "
		+ SPrint(m_backward) + " "
		+ SPrint(m_forward);
}

size_t BidirectionalReorderingState::hash() const
{
  size_t ret = m_backward->hash();
  boost::hash_combine(ret, m_forward->hash());

  cerr << "ret=" << ret << endl;
  return ret;
}

bool BidirectionalReorderingState::operator==(const FFState& o) const
{
  if (&o == this) return 0;

  BidirectionalReorderingState const &other
  = static_cast<BidirectionalReorderingState const&>(o);

  bool ret = (*m_backward == *other.m_backward) && (*m_forward == *other.m_forward);
  return ret;
}

void BidirectionalReorderingState::Expand(const System &system,
		  const LexicalReordering &ff,
		  const Hypothesis &hypo,
		  size_t phraseTableInd,
		  Scores &scores,
		  FFState &state) const
{
	cerr << "BidirectionalReorderingState::Expand" << endl;
}

} /* namespace Moses2 */
