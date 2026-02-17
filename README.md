# PIM-H: Plataforma Integrada de Monitoramento Hospitalar

Este projeto é uma solução IoT escalável projetada para modernizar a gestão de leitos e a segurança do paciente. Mais que um monitor de sensores, é uma estrutura de comunicação para a ficha digital do paciente à beira do leito.

## 🚀 Visão de Futuro e Potencial
O sistema foi construído sobre o princípio da **Modularidade Total**. A estrutura de dados JSON utilizada permite que o sistema cresça para incluir:
- ✅ **Controle de Medicamentos:** Alertas de horários integrados à farmácia.
- ✅ **Checklist de Enfermagem:** Registro digital de procedimentos realizados.
- ✅ **Sinais Vitais:** Integração direta com oxímetros e termômetros industriais.
- ✅ **Alertas Críticos:** Notificações instantâneas para intercorrências graves.

## 🛠️ Arquitetura Técnica
- **Comunicação:** Protocolo MQTT (Baixa latência e alta confiabilidade).
- **Processamento:** Gateway Inteligente que mapeia dinamicamente múltiplos leitos para a Nuvem.
- **Visualização:** Dashboard Cloud via ThingSpeak para monitoramento remoto.

## 📦 Como Escalar o Sistema
Para adicionar um novo leito ou uma nova funcionalidade (ex: sensor de batimentos):
1. **No Código do Leito:** Basta adicionar a nova variável no objeto JSON de publicação.
2. **No Gateway:** O sistema já está configurado para ouvir novos leitos (`hospital/leito/+/dados`). Ele identificará o novo ID automaticamente.
3. **Na Nuvem:** Basta habilitar novos Fields no ThingSpeak para receber os dados adicionais.

## 📂 Organização do Código
O código é separado por responsabilidades:
- `WifiManager`: Estabilidade da rede.
- `MqttManager`: Lógica de mensageria e tradução de dados.
- `CloudManager`: Interface de comunicação com o Prontuário Digital (Cloud).

---
**Este projeto representa o primeiro passo para uma unidade hospitalar totalmente conectada e inteligente.**
