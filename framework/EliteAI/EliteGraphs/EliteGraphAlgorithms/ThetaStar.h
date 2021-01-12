#pragma once

namespace Elite
{
	template <class T_NodeType, class T_ConnectionType>
	class ThetaStar
	{
	public:
		ThetaStar(IGraph<T_NodeType, T_ConnectionType>* pGraph, Heuristic hFunction);

		// stores the optimal connection to a node and its total costs related to the start and end node of the path
		struct NodeRecord
		{
			T_NodeType* pNode = nullptr;
			T_ConnectionType* pConnection = nullptr;
			float costSoFar = 0.f; // accumulated g-costs of all the connections leading up to this one
			float estimatedTotalCost = 0.f; // f-cost (= costSoFar + h-cost)

			bool operator==(const NodeRecord& other) const
			{
				return pNode == other.pNode
					&& pConnection == other.pConnection
					&& costSoFar == other.costSoFar
					&& estimatedTotalCost == other.estimatedTotalCost;
			};

			bool operator<(const NodeRecord& other) const
			{
				return estimatedTotalCost < other.estimatedTotalCost;
			};
		};

		std::vector<T_NodeType*> FindPath(T_NodeType* pStartNode, T_NodeType* pDestinationNode);

	private:
		float GetHeuristicCost(T_NodeType* pStartNode, T_NodeType* pEndNode) const;

		void CheckNextNodeNeighbor(T_NodeType* nextnode);

		IGraph<T_NodeType, T_ConnectionType>* m_pGraph;
		Heuristic m_HeuristicFunction;
	};

	template <class T_NodeType, class T_ConnectionType>
	ThetaStar<T_NodeType, T_ConnectionType>::ThetaStar(IGraph<T_NodeType, T_ConnectionType>* pGraph, Heuristic hFunction)
		: m_pGraph(pGraph)
		, m_HeuristicFunction(hFunction)
	{
	}
	
	template <class T_NodeType, class T_ConnectionType>
	std::vector<T_NodeType*> ThetaStar<T_NodeType, T_ConnectionType>::FindPath(T_NodeType* pStartNode, T_NodeType* pGoalNode)
	{
		std::vector<NodeRecord> openList;
		std::vector<NodeRecord> closedList;

		NodeRecord currentRecord{ pStartNode, nullptr, 0.f, GetHeuristicCost(pStartNode,pGoalNode) };
		openList.push_back(currentRecord);

		while (!openList.empty())
		{
			currentRecord.estimatedTotalCost = FLT_MAX;
			for (const auto& nodeRec : openList)
			{
				if (nodeRec.estimatedTotalCost <= currentRecord.estimatedTotalCost)
				{
					currentRecord = nodeRec;
				}
			}
			if (currentRecord.pNode == pGoalNode)
			{
				break;
			}

			for (const auto& con : m_pGraph->GetNodeConnections(currentRecord.pNode->GetIndex()))
			{
				T_NodeType* nextNode = m_pGraph->GetNode(con->GetTo());
				float G = currentRecord.costSoFar + con->GetCost();

				bool isValid{ true };

				for (size_t i = 0; i < closedList.size(); i++)
				{
					if (closedList[i].pNode == nextNode)
					{
						if (G <= closedList[i].costSoFar)
						{
							closedList.erase(closedList.begin() + i);
						}
						else
						{
							isValid = false;
						}
					}
				}

				for (size_t i = 0; i < openList.size(); i++)
				{
					if (openList[i].pNode == nextNode)
					{
						if (G <= openList[i].costSoFar)
						{
							openList.erase(openList.begin() + i);
						}
						else
						{
							isValid = false;
						}
					}
				}
				if (isValid)
				{
					openList.push_back(NodeRecord{ nextNode, con, G, GetHeuristicCost(nextNode, pGoalNode) + G });
				}
			}
			
			for (size_t i = 0; i < openList.size(); i++)
			{
				if (openList[i] == currentRecord)
				{
					openList.erase(openList.begin() + i);
					closedList.push_back(currentRecord);
				}
			}
		}


		//Track back
		vector<T_NodeType*> path;
		while (currentRecord.pNode != pStartNode)
		{
			path.push_back(currentRecord.pNode);

			T_NodeType* prevNode = m_pGraph->GetNode(currentRecord.pConnection->GetFrom());
			for (const auto& nodeRec : closedList)
			{
				if (nodeRec.pNode == prevNode)
				{
					currentRecord = nodeRec;
				}
			}
		}

		path.push_back(pStartNode);
		std::reverse(path.begin(), path.end());

		return path;
	}

	template <class T_NodeType, class T_ConnectionType>
	float Elite::ThetaStar<T_NodeType, T_ConnectionType>::GetHeuristicCost(T_NodeType* pStartNode, T_NodeType* pEndNode) const
	{
		Vector2 toDestination = m_pGraph->GetNodePos(pEndNode) - m_pGraph->GetNodePos(pStartNode);
		return m_HeuristicFunction(abs(toDestination.x), abs(toDestination.y));
	}
	template<class T_NodeType, class T_ConnectionType>
	inline void ThetaStar<T_NodeType, T_ConnectionType>::CheckNextNodeNeighbor(T_NodeType* nextnode)
	{



	}
}